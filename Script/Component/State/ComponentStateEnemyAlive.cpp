#include "../../Factory/FactoryComponent.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../Logic/ComponentLogicBase.h"
#include "ComponentStateEnemyAlive.h"

ComponentStateEnemyAlive::ComponentStateEnemyAlive(EnemyBase& owner) :
	ComponentCharacterStateBase(owner),
    sceneManager_(SceneManager::GetInstance()),
	owner_(owner)
{
    // 変数の初期化
    currentLogic_ = nullptr;
    delayTimer_ = 0.0f;

    // 状態遷移処理
    changeStateMap_.emplace(STATE::INTERVAL, std::bind(&ComponentStateEnemyAlive::ChangeStateInterval, this));
    changeStateMap_.emplace(STATE::LOGIC, std::bind(&ComponentStateEnemyAlive::ChangeStateLogic, this));
}

ComponentStateEnemyAlive::~ComponentStateEnemyAlive()
{
}

void ComponentStateEnemyAlive::Create()
{
    // 指定するロジックのコンポーネントを生成
    FactoryComponent& factory = FactoryComponent::GetInstance();

    // パラメータ取得
    const auto& logicMap = owner_.GetParameter().logicMap_;
    for (const auto& logicInfo : logicMap)
    {
        auto component = factory.CreateComponentLogicBase(logicInfo.first, owner_);
        component->Create();
        component->SetProbability(logicInfo.second);
        componentLogicMap_.emplace(logicInfo.first, std::move(component));
    }

    // 初期状態
    ChangeState(STATE::LOGIC);
}

void ComponentStateEnemyAlive::Init()
{
    // 現在のロジックが有効の場合
    if (currentLogic_)
    {
        // 攻撃判定を初期化
        currentLogic_->AttackReset();
    }
}

void ComponentStateEnemyAlive::Update()
{
    update_();
}

void ComponentStateEnemyAlive::Remove()
{
    // コンポーネントの取り外し
    for (auto& logic : componentLogicMap_)
    {
        if (logic.second)
        {
            logic.second->Remove();
        }
    }

    // 現在のロジックを空にする
    currentLogic_ = nullptr;
}

void ComponentStateEnemyAlive::UpdateInterval()
{
    // インターバル処理
    delayTimer_ -= sceneManager_.GetDeltaTime();

    // タイマー処理
    if (delayTimer_ < 0.0f)
    {
        ChangeState(STATE::LOGIC);
        return;
    }
}

void ComponentStateEnemyAlive::UpdateLogic()
{
    // ロジックが終了している、もしくはない場合
    if (currentLogic_ == nullptr || currentLogic_->IsEnd())
    {
        ChangeState(STATE::INTERVAL);
        return;
    }

    // ロジックが有効の場合
    if (currentLogic_)
    {
        // 更新処理を実行
        currentLogic_->Update();
    }
}

void ComponentStateEnemyAlive::ChangeState(const STATE state)
{
    state_ = state;
    changeStateMap_[state_]();
}

void ComponentStateEnemyAlive::ChangeStateInterval()
{
    update_ = std::bind(&ComponentStateEnemyAlive::UpdateInterval, this);

    // 遅延時間を設定
    delayTimer_ = owner_.GetParameter().logicDelay_;
}

void ComponentStateEnemyAlive::ChangeStateLogic()
{
    update_ = std::bind(&ComponentStateEnemyAlive::UpdateLogic, this);

    // 抽選
    SelectNextLogic();
}

void ComponentStateEnemyAlive::SelectNextLogic()
{
    // 初期化
    currentLogic_ = nullptr;

    // 所有者がロジックを持たない場合
    if (componentLogicMap_.empty())
    {
        // 終了
        return;
    }

    // 確率の合計を計算
    float totalProbability = 0.0f;
    std::vector<ComponentLogicBase*> activeLogics;  // 有効な
    for (const auto& pair : componentLogicMap_)
    {
        if (pair.second != nullptr)
        {
            // 確率の取得
            float prob = pair.second->GetProbability();
            if (prob > 0.0f)
            {
                totalProbability += prob;
                activeLogics.push_back(pair.second.get());
            }
        }
    }

    if (activeLogics.empty() || totalProbability <= 0.0f)
    {
        return;
    }

    float randValue = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * totalProbability;
    float currentSum = 0.0f;

    for (auto* logic : activeLogics)
    {
        currentSum += logic->GetProbability();
        if (randValue <= currentSum)
        {
            currentLogic_ = logic;
            currentLogic_->Init();
            break;
        }
    }
}