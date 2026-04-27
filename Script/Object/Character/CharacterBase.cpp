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

void CharacterBase::Draw()
{
	if (state_ == STATE::DEAD) { return; }
	ActorBase::Draw();
}

void CharacterBase::DebugDraw()
{
	// 自身の体力を描画
	DrawFormatString(
		characterParameterPtr_->pos.x - characterParameterPtr_->hitBoxSize.x / 2,
		characterParameterPtr_->pos.y - characterParameterPtr_->hitBoxSize.y / 2 -20,
		UtilityCommon::RED,
		L"AT:%d",
		characterParameterPtr_->attackPower);

	DrawFormatString(
		characterParameterPtr_->pos.x - characterParameterPtr_->hitBoxSize.x / 2,
		characterParameterPtr_->pos.y - characterParameterPtr_->hitBoxSize.y / 2 -40,
		UtilityCommon::RED,
		L"HP:%d",
		characterParameterPtr_->hp);
}

void CharacterBase::ChangeState(const STATE state)
{
	state_ = state;
}

void CharacterBase::Damage(const int damage)
{
	// 体力を減らす
	characterParameterPtr_->hp -= damage;

	// 体力が0以下の場合
	if (characterParameterPtr_->hp <= 0)
	{
		ChangeState(STATE::DEAD);
	}
}

const int CharacterBase::GetAttackPower() const
{
	return characterParameterPtr_->attackPower;
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