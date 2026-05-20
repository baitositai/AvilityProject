#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../../Factory/FactoryComponent.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Component/ComponentBase.h"
#include "../../Collider/ColliderBase.h"
#include "../../Parameter/Character/ParameterCharacter.h"
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
	ActorBase::Init();

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

void CharacterBase::DebugDraw()
{
	// 自身の体力を描画
	DrawFormatString(
		parameterCharacter_->pos_.x - parameterCharacter_->hitSize_.x / 2,
		parameterCharacter_->pos_.y - parameterCharacter_->hitSize_.y / 2 -20,
		UtilityCommon::RED,
		L"AT:%d",
		parameterCharacter_->attackPower_);

	DrawFormatString(
		parameterCharacter_->pos_.x - parameterCharacter_->hitSize_.x / 2,
		parameterCharacter_->pos_.y - parameterCharacter_->hitSize_.y / 2 -40,
		UtilityCommon::RED,
		L"HP:%d",
		parameterCharacter_->hp_);
}

void CharacterBase::ChangeState(const STATE state)
{
	state_ = state;
}

void CharacterBase::Damage(const int damage)
{
	// 体力を減らす（ダメージ率だけダメージ量を変える）
	parameterCharacter_->hp_ -= damage * (1 + parameterCharacter_->damageRate_);

	// 体力が0以下の場合
	if (parameterCharacter_->hp_ <= 0)
	{
		// 体力を0にする
		parameterCharacter_->hp_ = 0;

		// 状態変更
		ChangeState(STATE::DEAD);

		// コライダーの判定を無効にする
		collider_->SetIsActive(false);

		// アニメーション開始
		animation_->Play(Animation::TYPE::DEAD, false);
		animation_->SetNextAnimationType(Animation::TYPE::MAX);

		// ジャンプを更新しない
		SetComponentActive("jump", false);
		return;
	}

	// 無敵時間の設定
	parameterCharacter_->invincibleTime_ = parameterCharacter_->invincibleTimeMax_;

	// アニメーション設定
	animation_->Play(Animation::TYPE::DAMAGE, false);

	// 次回アニメーション設定
	animation_->SetNextAnimationType(Animation::TYPE::IDLE);

	// 状態遷移
	ChangeState(STATE::ALIVE);
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

const int CharacterBase::GetAttackPowerWithBoost() const
{
	float boostAttackPower = static_cast<float>(parameterCharacter_->attackPower_) * (1.0f + parameterCharacter_->attackBoostRate_);
	return static_cast<int>(boostAttackPower);
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
	// 状態別コンポーネントの取得
	for (const auto & name : parameterCharacter_->stateComponentKeys_)
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