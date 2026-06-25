#include "../../Factory/FactoryComponent.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../Logic/ComponentLogicBase.h"
#include "ComponentStateEnemyAlive.h"

ComponentStateEnemyAlive::ComponentStateEnemyAlive(EnemyBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner)
{
    currentLogic_ = nullptr;
}

ComponentStateEnemyAlive::~ComponentStateEnemyAlive()
{
}

void ComponentStateEnemyAlive::Create()
{
    FactoryComponent& factory = FactoryComponent::GetInstance();

    const auto& logicMap = owner_.GetParameter().logicMap_;
    for (const auto& logicInfo : logicMap)
    {
        auto component = factory.CreateComponentLogicBase(logicInfo.first, owner_);
        component->Create();
        component->SetProbability(logicInfo.second);
        componentLogicMap_.emplace(logicInfo.first, std::move(component));
    }

    // 初期化
    Init();
}

void ComponentStateEnemyAlive::Init()
{
    // 最初のロジックを抽選
    SelectNextLogic();
}

void ComponentStateEnemyAlive::Update()
{
    // ロジックが終了している、もしくはない場合
    if (currentLogic_ == nullptr || currentLogic_->IsEnd())
    {
        // 抽選
        SelectNextLogic();
    }

    // ロジックが有効の場合
    if (currentLogic_)
    {    
        // 更新処理を実行
        currentLogic_->Update();
    }
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