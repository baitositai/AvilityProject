#include "../Manager/Common/SceneManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Common/Animation.h"
#include "ComponentJump.h"

ComponentJump::ComponentJump(CharacterBase& owner) :
	ComponentBase(&owner),
	owner_(owner),
	scnMng_(SceneManager::GetInstance()),
	animation_(owner_.GetAnimation())
{
}

ComponentJump::~ComponentJump()
{
}

void ComponentJump::Update()
{
	if (owner_.IsGround())
	{
		return;
	}

	// ジャンプ量取得
	float currentJumpPow = owner_.GetJumpPow();

	// 加算
	const float ATTENUATION = owner_.GetParameter()->gravityPower * scnMng_.GetDeltaTime() * 3.0f;
	currentJumpPow += ATTENUATION;

	if (currentJumpPow > 0.0f)
	{
		currentJumpPow = 0.0f;
	}

	// ジャンプ量更新
	owner_.SetJumpPow(currentJumpPow);

	// 移動量の更新
	Vector2F moveAmount = owner_.GetParameter()->moveAmount;
	moveAmount.y += currentJumpPow;
	owner_.SetMoveAmount(moveAmount);

	// アニメーション切り替え
	const float HIGHEST = -owner_.GetJumpPowMax() / 2.0f + 2.0f;
	if (currentJumpPow >= HIGHEST)
	{
		// アニメーションの種類を取得
		Animation::TYPE type = animation_.GetType();

		// 落下中、もしくは攻撃中の場合は無視
		if (type != Animation::TYPE::FALL && type != Animation::TYPE::ATTACK)
		{
			animation_.Play(Animation::TYPE::FALL);
		}
	}
}
