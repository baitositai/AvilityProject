#include "../../../Manager/Common/InputManager.h"
#include "../../../Manager/Common/SceneManager.h"
#include "../../../Object/Character/Player.h"
#include "../../../Object/Common/Animation.h"
#include "ComponentStatePlayerAlive.h"

ComponentStatePlayerAlive::ComponentStatePlayerAlive(Player& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	inputManager_(InputManager::GetInstance())
{
	velocityY_ = 0.0f;
	isGround_ = false;
}

ComponentStatePlayerAlive::~ComponentStatePlayerAlive()
{
}

void ComponentStatePlayerAlive::Update()
{
	// 移動量の初期化
	moveAmount_ = {};

	// 現在の地面判定取得
	isGround_ = owner_.IsGround();

	// 移動の入力処理
	ProcessInputMove();

	// ジャンプの入力処理
	ProcessInputJump();

	// ジャンプ処理
	Jump();	
	
	// 通常攻撃の入力処理
	ProcessInputAttack();

	// 情報の更新
	owner_.SetMoveAmount(moveAmount_);
	owner_.SetIsGround(isGround_);
}

void ComponentStatePlayerAlive::ProcessInputMove()
{
	// ダッシュの入力判定に応じて速度を変更
	const float moveSpeed = inputManager_.IsNew(InputManager::TYPE::PLAYER_DASH) ? owner_.GetDashSpeed() : owner_.GetParameter()->moveSpeed;

	// 左右移動
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT))
	{
		moveAmount_.x = moveSpeed;
		owner_.SetDirection(false);
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT))
	{
		moveAmount_.x = -moveSpeed;
		owner_.SetDirection(true);
	}

	// 地面にいる場合
	if (isGround_)
	{
		// 移動量がある場合
		if (moveAmount_.x > 0.0f || moveAmount_.x < 0.0f)
		{
			// 走るアニメーションの変更
			owner_.GetAnimation().Play(Animation::TYPE::WALK);
		}
		else
		{
			// 待機のアニメーションに変更
			owner_.GetAnimation().Play(Animation::TYPE::IDLE);
		}
	}
}

void ComponentStatePlayerAlive::ProcessInputJump()
{
	if (isGround_)
	{
		// Python: if キー入力があったら:
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_JUMP))
		{
			// Python: canJump = False
			isGround_ = false;

			// Python: vel = -10 (初速を与える)
			// jumpPowMaxを 10.0f ～ 15.0f 程度にすると緩やかになります
			owner_.SetJumpPow(-owner_.GetJumpPowMax());

			owner_.GetAnimation().Play(Animation::TYPE::JUMP);
		}
	}
}

void ComponentStatePlayerAlive::ProcessInputAttack()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_ATTACK))
	{
		// 攻撃のアニメーションを開始（ループしない）
		owner_.GetAnimation().Play(Animation::TYPE::ATTACK, false);

		// 次回アニメーションを指定しない
		owner_.GetAnimation().SetNextAnimationType(Animation::TYPE::MAX);

		// 状態遷移
		owner_.ChangeState(Player::STATE::ATTACK);

		// 攻撃の初期化
		owner_.AttackReset();
		
		// 横移動の値をなくす
		moveAmount_.x = 0.0f;
	}
}

void ComponentStatePlayerAlive::Jump()
{
	// 地面にいる場合何もしない
	if (isGround_) return;

	// 情報の取得・定義
	float currentJumpPow = owner_.GetJumpPow();	// 現在のジャンプ量
	const float JUMP_ACC = owner_.GetParameter()->gravityPower * SceneManager::GetInstance().GetDeltaTime() * 3.0f;	// 加速度
	const float HIGHEST = -owner_.GetJumpPowMax() / 2.0f + 2.0f;	// ジャンプ最高点(遅めに切り替えるよう少し調整)

	// 速度に加速度を加える
	currentJumpPow += JUMP_ACC;

	// ジャンプ量を設定
	owner_.SetJumpPow(currentJumpPow);

	// 移動量を更新
	moveAmount_.y = currentJumpPow;

	// 最高点に達した場合
	if (currentJumpPow >= HIGHEST)
	{
		owner_.GetAnimation().Play(Animation::TYPE::FALL);
	}
}