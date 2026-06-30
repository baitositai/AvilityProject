#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Game/UiManager.h"
#include "../../Factory/FactoryComponent.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Component/ComponentBase.h"
#include "../../Collider/ColliderBox.h"
#include "../../Parameter/Character/ParameterCharacter.h"
#include "../../Ui/Game/UiDamage.h"
#include "../Common/Animation.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase(std::unique_ptr<ParameterCharacter> parameter) :
	ActorBase(std::move(parameter))
{
	// パラメータ情報
	parameterCharacter_ = dynamic_cast<ParameterCharacter*>(GetParameterActorPtr());
	assert(parameterCharacter_ != nullptr);

	// 変数の初期化
	type_ = TYPE::MAX;
	state_ = STATE::MAX;
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Init()
{
	// 基底クラスの処理
	ActorBase::Init();

	// 状態別コンポーネントの初期化
	for(auto& component : componentStateMap_)
	{
		component.second->Init();
	}

	// 初期状態を設定
	ChangeState(STATE::ALIVE);
}

void CharacterBase::Update()
{
	// 移動後の値を初期化
	parameterCharacter_->moveAmount_ = {};

	UpdateComponentState();
	
	// 基底クラスの処理
	ActorBase::Update();
}

void CharacterBase::Draw()
{
	if (IsInvincible())
	{
		// 点滅の1周期にかかる時間
		constexpr int BLINK_CYCLE_MS = 200;

		// 現在の時間を取得
		int nowTime = GetNowCount();

		// 周期に基づいて角度を計算
		float currentAngle = (nowTime % BLINK_CYCLE_MS) * DX_PI_F * 2.0f / static_cast<float>(BLINK_CYCLE_MS);

		// サイン波を使って範囲変換
		int alphaValue = static_cast<int>((sin(currentAngle) + 1.0f) * (UtilityCommon::ALPHA_MAX / 2.0f));

		// アルファ値を変更して点滅
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
		ActorBase::Draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		ActorBase::Draw();
	}
}

void CharacterBase::Delete()
{
	// 状態別コンポーネントの削除処理
	for (auto& it : componentStateMap_)
	{
		it.second->Remove();
	}
	componentStateMap_.clear();

	ActorBase::Delete();
}

void CharacterBase::DebugDraw()
{
	// 自身の体力を描画
	DrawFormatString(
		parameterCharacter_->drawPos_.x - parameterCharacter_->hitSize_.x / 2,
		parameterCharacter_->drawPos_.y - parameterCharacter_->hitSize_.y / 2 -20,
		UtilityCommon::RED,
		L"AT:%d",
		GetAttackPowerWithBoost());

	DrawFormatString(
		parameterCharacter_->drawPos_.x - parameterCharacter_->hitSize_.x / 2,
		parameterCharacter_->drawPos_.y - parameterCharacter_->hitSize_.y / 2 -40,
		UtilityCommon::RED,
		L"HP:%d",
		parameterCharacter_->hp_);
}

void CharacterBase::ChangeState(const STATE state)
{
	// 状態設定
	state_ = state;

	// 初期化処理
	componentStateMap_.at(state_)->Init();
}

void CharacterBase::Damage(const int damage, const Vector2& hitPos)
{
	// 体力を減らす（ダメージ率だけダメージ量を変える）
	float newDamage =  static_cast<float>(damage) * (1.0f - parameterCharacter_->defenseRate_);
	parameterCharacter_->hp_ -= static_cast<float>(newDamage);

	// ダメージUIの作成
	uiMng_.Add(std::move(std::make_unique<UiDamage>(newDamage, hitPos, parameterCharacter_->damageColor_)));

	// 体力が0以下の場合
	if (parameterCharacter_->hp_ <= 0)
	{
		// 死亡処理
		Dead();
		return;
	}

	// 攻撃のリセット
	AttackReset();
}

void CharacterBase::Dead()
{
	// 体力を0にする
	parameterCharacter_->hp_ = 0;

	// 状態変更
	ChangeState(STATE::DEAD);

	// コライダーの判定を無効にする
	collider_->SetIsActive(false);

	// 攻撃の初期化
	componentStateMap_.at(STATE::ATTACK)->Init();

	// 攻撃判定無効
	parameterCharacter_->isAction_ = false;

	// アニメーション開始
	animation_->Play(Animation::TYPE::DEAD, false);
	animation_->SetNextAnimationType(Animation::TYPE::MAX);

	// ジャンプを更新しない
	SetComponentActive("jump", false);
}

void CharacterBase::AttackReset()
{
	// 攻撃の初期化
	componentStateMap_.at(STATE::ATTACK)->Init();

	// 状態遷移
	ChangeState(STATE::ALIVE);

	// 攻撃判定無効
	parameterCharacter_->isAction_ = false;
}

void CharacterBase::AttackAfter()
{
	// 状態遷移
	ChangeState(STATE::ALIVE);

	// アニメーション
	animation_->Play(Animation::TYPE::IDLE);
}

void CharacterBase::SetJumpPow(const float jumpPow)
{
	parameterCharacter_->jumpPow_ = jumpPow;
	if (parameterCharacter_->jumpPow_ > 0.0f) parameterCharacter_->jumpPow_ = 0.0f;
}

void CharacterBase::Landing()
{
	// ジャンプ回数を戻す
	parameterCharacter_->jumpCount_ = parameterCharacter_->jumpCountMax_;

	// 着地判定
	parameterCharacter_->isGround_ = true;
}

const bool CharacterBase::IsInvincible() const
{
	return parameterCharacter_->invincibleTime_ > 0.0f;
}

void CharacterBase::UpdateComponentState()
{
	// マップから現在の状態のものがあるか探す
	auto it = componentStateMap_.find(state_);

	// 存在する場合
	if (it != componentStateMap_.end() && it->second)
	{
		// 状態別コンポーネントがアクティブな場合は更新する
		if (it->second->IsActive())
		{
			// 更新処理
			it->second->Update();
		}
	}
}

void CharacterBase::CreateComponents()
{
	// 空じゃない場合
	if (!componentStateMap_.empty())
	{
		// 取り外し兼削除
		for (const auto& component : componentStateMap_)
		{
			component.second->Remove();
		}
		componentStateMap_.clear();
	}

	// 指定しターキーのコンポーネントの作成
	for (const auto& name : parameterCharacter_->stateComponentKeys_)
	{
		// 指定のキーが登録できるか探索
		auto it = NAME_TO_STATE_MAP.find(name.first);
		if (it == NAME_TO_STATE_MAP.end())
		{
			// 次へ
			continue;
		}

		// コンポーネントの生成
		auto component = facCom_.CreateComponent(name.second, *this);

		// 生成できた場合生成処理
		if (component) { component->Create(); }

		// 登録
		auto result = componentStateMap_.emplace(it->second, std::move(component));

		// 登録の失敗時のアサ―ト
		assert(result.second && "状態別コンポーネントの追加に失敗しています");
	}

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

std::shared_ptr<ColliderBox> CharacterBase::CreateColliderClone()
{
	std::shared_ptr<ColliderBase> collider = collider_->Clone();
	std::shared_ptr<ColliderBox> colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider);
	colliderBox->SetIsActive(false);
	colliderBox->SetIsRegister(false);
	return colliderBox;
}