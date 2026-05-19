#include "../Manager/Common/SceneManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Common/Animation.h"
#include "ComponentJump.h"

ComponentJump::ComponentJump(CharacterBase& owner) :
	ComponentBase(owner),
	owner_(owner),
	parameter_(owner_.GetParameter()),
	scnMng_(SceneManager::GetInstance()),
	animation_(owner_.GetAnimation())
{
}

ComponentJump::~ComponentJump()
{
}

void ComponentJump::Update()
{
	if (parameter_.isGround_)
	{
		return;
	}

	// ジャンプ量取得
	float currentJumpPow = parameter_.jumpPow_;

	// 加算
	const float ATTENUATION = owner_.GetGravityPowerWithBoost() * scnMng_.GetDeltaTime() * 3.0f;
	currentJumpPow += ATTENUATION;

	if (currentJumpPow > 0.0f)
	{
		currentJumpPow = 0.0f;
	}

	// ジャンプ量更新
	owner_.SetJumpPow(currentJumpPow);

	// 移動量の更新
	Vector2F moveAmount = parameter_.moveAmount_;
	moveAmount.y += currentJumpPow;
	parameter_.moveAmount_ = moveAmount;

	// アニメーション切り替え
	const float HIGHEST = -parameter_.jumpPowMax_ / 2.0f + 2.0f;
	if (currentJumpPow >= HIGHEST)
	{
		// アニメーションの種類を取得
		Animation::TYPE type = animation_.GetType();

		// 落下中、もしくは攻撃中の場合は無視
		if (type != Animation::TYPE::FALL && 
			type != Animation::TYPE::ATTACK &&
			type != Animation::TYPE::DAMAGE)
		{
			animation_.Play(Animation::TYPE::FALL);
		}
	}
}
