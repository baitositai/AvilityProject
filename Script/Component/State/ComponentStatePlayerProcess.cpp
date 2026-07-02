#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentStatePlayerProcess.h"

ComponentStatePlayerProcess::ComponentStatePlayerProcess(Player& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter()),
	inputManager_(InputManager::GetInstance())
{
	velocityY_ = 0.0f;
	isGround_ = false;
}

ComponentStatePlayerProcess::~ComponentStatePlayerProcess()
{
}

void ComponentStatePlayerProcess::Update()
{
	// 移動量の初期化
	moveAmount_ = {};

	// 現在の地面判定取得
	isGround_ = parameter_.isGround_;

	// 移動の入力処理
	ProcessInputMove();

	// ジャンプの入力処理
	ProcessInputJump();
	
	// 通常攻撃の入力処理
	ProcessInputAttack();

	// 重力方向に応じて移動量を変換
	moveAmount_ = UtilityCommon::ConvertLocalToWorldByGravity(moveAmount_, parameter_.gravityDir_);

	// 情報の更新
	parameter_.moveAmount_ = moveAmount_;
	parameter_.isGround_ = isGround_;
}

void ComponentStatePlayerProcess::ProcessInputMove()
{
	// ダッシュの入力判定に応じて速度を変更
	float moveSpeed = inputManager_.IsNew(InputManager::TYPE::PLAYER_DASH, parameter_.padNo_) ? parameter_.dashSpeed_ : parameter_.moveSpeed_;

	// ダッシュ上昇率を乗算
	moveSpeed *= 1 + parameter_.moveSpeedBoostRate_;

	// 左右移動
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT, parameter_.padNo_))
	{
		moveAmount_.x = moveSpeed;
		parameter_.direction_ = false;
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT, parameter_.padNo_))
	{
		moveAmount_.x = -moveSpeed;
		parameter_.direction_ = true;
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

void ComponentStatePlayerProcess::ProcessInputJump()
{
	if (parameter_.jumpCount_ > 0)
	{
		// 入力がある場合
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_JUMP, parameter_.padNo_) && !parameter_.isHitItem_)
		{
			// 非陸状態
			isGround_ = false;

			// ジャンプ力設定
			owner_.SetJumpPow(-parameter_.jumpPowMax_);

			// アニメーション再生
			owner_.GetAnimation().Play(Animation::TYPE::JUMP);

			// ジャンプ回数減少
			parameter_.jumpCount_--;

			// ノックバック初期化
			parameter_.knockBackPower_ = {};
		}
	}
}

void ComponentStatePlayerProcess::ProcessInputAttack()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_ATTACK, parameter_.padNo_) && !parameter_.isAction_)
	{
		// 攻撃のアニメーションを開始（ループしない）
		owner_.GetAnimation().Play(Animation::TYPE::ATTACK, false);

		// 次回アニメーションを指定しない
		owner_.GetAnimation().SetNextAnimationType(Animation::TYPE::MAX);

		// 状態遷移
		owner_.ChangeState(Player::STATE::ATTACK);

		// アビリティを無効にする
		owner_.SetAllAvilityComponentActive(false);

		// アクション判定を有効
		parameter_.isAction_ = true;
		
		// 横移動の値をなくす
		moveAmount_.x = 0.0f;
	}
}