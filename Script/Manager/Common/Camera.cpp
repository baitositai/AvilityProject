#include <algorithm>
#include "../../Application.h"
#include "../../Manager/Common/InputManager.h"
#include "Camera.h"

Camera::Camera() :
	inputMng_(InputManager::GetInstance())
{	
	// 変数の初期化
	mode_ = MODE::NONE;
	pos_ = Vector2F();
	limitMax_ = Vector2F();
	limitMin_ = Vector2F();
	followPos_ = {};

	// モード別状態遷移処理
	changeStateMap_.emplace(MODE::FREE, std::bind(&Camera::ChangeModeFree, this));
	changeStateMap_.emplace(MODE::FIXED_POINT, std::bind(&Camera::ChangeModeFixedPoint, this));
	changeStateMap_.emplace(MODE::PLAYER_FOLLOW, std::bind(&Camera::ChangeModePlayerFollow, this));
}

Camera::~Camera()
{
}

void Camera::Init()
{
	// 初期モードは固定点
	ChangeMode(MODE::FIXED_POINT);
}

void Camera::Update()
{
	// カメラのモードに応じた更新処理
	updateFunction_();

	// カメラの移動制限
	LimitCameraMove();
}

void Camera::ChangeMode(const MODE mode)
{
	// カメラのモード
	mode_ = mode;

	// カメラ別モードの設定
	changeStateMap_.at(mode)();
}

void Camera::UpdateModeFree()
{
	// 自由操作
	if(inputMng_.IsNew(InputManager::TYPE::CAMERA_MOVE_RIGHT)) { pos_.x -= CAMERA_MOVE_SPEED; }
	if(inputMng_.IsNew(InputManager::TYPE::CAMERA_MOVE_LEFT)) { pos_.x += CAMERA_MOVE_SPEED; }
	if(inputMng_.IsNew(InputManager::TYPE::CAMERA_MOVE_UP)) { pos_.y += CAMERA_MOVE_SPEED; }
	if(inputMng_.IsNew(InputManager::TYPE::CAMERA_MOVE_DOWN)) { pos_.y -= CAMERA_MOVE_SPEED; }
}

void Camera::UpdateModeFixedPoint()
{
}

void Camera::UpdateModePlayerFollow()
{
	pos_.x = (float)Application::SCREEN_HALF_X - followPos_->x;
	pos_.y = (float)Application::SCREEN_HALF_Y - followPos_->y;
}

void Camera::ChangeModeFree()
{
	updateFunction_ = std::bind(&Camera::UpdateModeFree, this);
}

void Camera::ChangeModeFixedPoint()
{
	updateFunction_ = std::bind(&Camera::UpdateModeFixedPoint, this);
}

void Camera::ChangeModePlayerFollow()
{
	updateFunction_ = std::bind(&Camera::UpdateModePlayerFollow, this);
}

void Camera::LimitCameraMove()
{
	// カメラがマイナス方向に動ける最大の限界値（正の数として計算）
	// limitMax_ はステージの総サイズと仮定
	float maxMoveX = limitMax_.x - static_cast<float>(Application::SCREEN_SIZE_X);
	float maxMoveY = limitMax_.y - static_cast<float>(Application::SCREEN_SIZE_Y);

	// ステージが画面サイズより小さい場合は 0 固定にする安全対策
	if (maxMoveX < 0.0f)
	{
		maxMoveX = 0.0f;
	}
	if (maxMoveY < 0.0f)
	{
		maxMoveY = 0.0f;
	}

	// カメラの座標は 0 から -maxMove の範囲に収まる必要がある
	// std::clamp の引数は必ず [小さい値, 大きい値] にする
	pos_.x = std::clamp(pos_.x, -maxMoveX, 0.0f);
	pos_.y = std::clamp(pos_.y, -maxMoveY, 0.0f);
}
