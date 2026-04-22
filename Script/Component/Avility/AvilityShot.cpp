#include "../../Common/Vector2F.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Player.h"

#include "AvilityShot.h"

AvilityShot::AvilityShot(Player& owner)
    : ComponentAvilityBase(owner),
	inputManager_(InputManager::GetInstance()),
	moveAmount_({}),
	shotCount_(0.0f)
{
	stateFunctionMap_=
	{
		{"shot", [this]() { return ProcessInputShot(); }},
		{"move", [this]() { return ProcessMoveShot(); }}
	};
	currentState_ = "shot";
	currentStateFunction_ = stateFunctionMap_[currentState_];
}

AvilityShot::~AvilityShot()
{
}

void AvilityShot::Update()
{
    int x = 0;
	// 移動量の初期化
	moveAmount_ = {};

	currentStateFunction_();

	// 移動量の更新
	owner_.AddMoveAmount(moveAmount_);
}


void AvilityShot::ProcessInputShot()
{
	const float moveSpeed = owner_.GetParameter()->moveSpeed;

	shotVec_ = {};
	// 方向判定
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT))
	{
		shotVec_.x += 1;
	}
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT))
	{
		shotVec_.x -= 1;
	}
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_UP))
	{
		shotVec_.y -= 1;
	}
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_DOWN))
	{
		shotVec_.y += 1;
	}

	if (inputManager_.IsNew(InputManager::TYPE::CAMERA_MODE_CHANGE))
	{
		// 横の移動量がゼロなら現在の向きを入れる
		if (shotVec_.x == 0)
		{
			shotVec_.x = owner_.GetParameter()->direction ? -1 : 1;
		}


		shotCount_ = 2.0f;

		currentState_ = "move";
		currentStateFunction_ = stateFunctionMap_[currentState_];
	}
}

void AvilityShot::ProcessMoveShot()
{
	shotCount_ -= 0.1f;

	if (shotCount_ <= 0.0f)
	{
		currentState_ = "shot";
		currentStateFunction_ = stateFunctionMap_[currentState_];
		return;
	}
	else
	{
		moveAmount_.y = shotVec_.y * shotCount_ * SHOT_SPEED;
		moveAmount_.x = shotVec_.x * shotCount_ * SHOT_SPEED;
	}

}
