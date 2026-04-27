#include "../../Common/Vector2F.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Player.h"
#include "../../Object/ActorBase.h"

#include "ComponentAvilityChargeShot.h"

ComponentAvilityChargeShot::ComponentAvilityChargeShot(Player& owner)
	: ComponentAvilityBase(owner),
	inputManager_(InputManager::GetInstance()),
	moveAmount_({}),
	shotTime_(0.0f)
{
	stateFunctionMap_ =
	{
		{"shot", [this]() { return ProcessInputShot(); }},
		{"charge", [this]() { return ProcessInputCharge(); }},
		{"move", [this]() { return ProcessMoveShot(); }}
	};
	currentState_ = "shot";
	currentStateFunction_ = stateFunctionMap_[currentState_];
}

ComponentAvilityChargeShot::~ComponentAvilityChargeShot()
{
}

void ComponentAvilityChargeShot::Update()
{
	int x = 0;
	// 移動量の初期化
	moveAmount_ = {};

	currentStateFunction_();

}


void ComponentAvilityChargeShot::ProcessInputShot()
{
	// 横向きにしか撃てないようにするため、縦の入力は無視する
	const float moveSpeed = owner_.GetParameter()->moveSpeed;

	//　ショット入力があったらCharge開始(現在Qキー)
	if (inputManager_.IsNew(InputManager::TYPE::LIGHT_SWITCH))
	{
		currentState_ = "charge";
		currentStateFunction_ = stateFunctionMap_[currentState_];
	}
}

void ComponentAvilityChargeShot::ProcessInputCharge()
{

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

	// 横の移動量がゼロなら現在の向きを入れる
	if (shotVec_.x == 0)
	{
		shotVec_.x = owner_.GetParameter()->direction ? -1 : 1;
	}
	owner_.SetShotVec(shotVec_);

	//　ショット入力があったらCharge開始(現在Qキー)
	if (inputManager_.IsNew(InputManager::TYPE::LIGHT_SWITCH))
	{
	}
	else{

		shotTime_ = 2.0f;

		currentState_ = "shot";
		currentStateFunction_ = stateFunctionMap_[currentState_];
	}
}

void ComponentAvilityChargeShot::ProcessMoveShot()
{
	shotTime_ -= 0.1f;

	if (shotTime_ <= 0.0f)
	{
		currentState_ = "shot";
		currentStateFunction_ = stateFunctionMap_[currentState_];
		return;
	}
	else
	{
		//// ぶつかっていた場合shotVec_を９０度変更する
		//if(owner_.)
		//{
		//	float temp = shotVec_.x;
		//	shotVec_.x = -shotVec_.y;
		//	shotVec_.y = temp;
		//}

		Vector2F dir = owner_.GetShotVec();

		moveAmount_.y = dir.y * shotTime_ * SHOT_SPEED;
		moveAmount_.x = dir.x * shotTime_ * SHOT_SPEED;

	}

	// 移動量の更新
	owner_.SetMoveAmount(moveAmount_);
}
