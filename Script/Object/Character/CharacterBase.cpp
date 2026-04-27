#include <DxLib.h>
#include "../../Factory/FactoryComponent.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Component/ComponentBase.h"
#include "../../Collider/ColliderBase.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase(Parameter* parameter, const std::unordered_map<std::string, std::string> stateComponentNameMap, const std::vector<std::string> defaultComponentNameList)	:
	ActorBase(parameter, defaultComponentNameList),
	STATE_COMPONENT_CREATE_MAP(stateComponentNameMap),
	characterParameterPtr_(parameter)
{	
	state_ = STATE::MAX;

	// 状態遷移処理の登録
	//stateChangeMap_.emplace(STATE::ALIVE, std::bind(&CharacterBase::ChangeStateAlive, this));
	//stateChangeMap_.emplace(STATE::ATTACK, std::bind(&CharacterBase::ChangeStateAttack, this));
	//stateChangeMap_.emplace(STATE::HIT, std::bind(&CharacterBase::ChangeStateHit, this));
	//stateChangeMap_.emplace(STATE::DEAD, std::bind(&CharacterBase::ChangeStateDead, this));
	//stateChangeMap_.emplace(STATE::RESPAWN, std::bind(&CharacterBase::ChangeStateRespawn, this));
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Init()
{
	ActorBase::Init();

	// 初期状態を設定
	ChangeState(STATE::ALIVE);
}

void CharacterBase::Update()
{
	// マップから現在の状態のものがあるか探す
	auto it = componentStateMap_.find(state_);

	// 存在する場合
	if (it != componentStateMap_.end() && it->second)
	{
		// 更新処理
		it->second->Update();
	}

	// 基底クラスの処理
	ActorBase::Update();
}

void CharacterBase::DebugDraw()
{
}

void CharacterBase::ChangeState(const STATE state)
{
	state_ = state;
}

void CharacterBase::CreateComponents()
{
	// 状態別コンポーネントの取得
	for (const auto & name : STATE_COMPONENT_CREATE_MAP)
	{
		// 状態の名前が取得できているか確認
		auto it = NAME_TO_STATE_MAP.find(name.first);

		// ない場合次へ
		if (it == NAME_TO_STATE_MAP.end()) { continue; }

		// 同名のコンポーネントが既に存在するか確認しながら挿入
		auto result = componentStateMap_.emplace(NAME_TO_STATE_MAP.at(name.first), std::move(facCom_.CreateComponent(name.second, *this)));

		// 挿入に成功してるか確認
		assert(result.second && "状態別コンポーネントの追加に失敗しています");
	}

	// 基底クラスの処理
	ActorBase::CreateComponents();
}

bool CharacterBase::IsStateComponentActive(const STATE state) const
{
	// 指定された名前の要素を検索する
	auto it = componentStateMap_.find(state);

	// 要素が見つかった場合は削除する
	if (it != componentStateMap_.end())
	{
		return it->second->IsActive();
	}
}

void CharacterBase::SetStateComponentActive(const STATE state, const bool isActive)
{
	// 指定された名前の要素を検索する
	auto it = componentStateMap_.find(state);

	// 要素が見つかった場合は削除する
	if (it != componentStateMap_.end())
	{
		return it->second->SetActive(isActive);
	}
}