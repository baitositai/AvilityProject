#include <algorithm>
#include "../../Application.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "Camera.h"

Camera::Camera() :
	inputMng_(InputManager::GetInstance()),
	scnMng_(SceneManager::GetInstance())
{	
	// 変数の初期化
	shakePower_ = 0.0f;
	shakeTime_ = 0.0f;
	mode_ = MODE::NONE;
	pos_ = Vector2F();
	limitMax_ = Vector2F();
	limitMin_ = Vector2F();
	followPos_ = {};
	offset_ = {};

	// モード別状態遷移処理
	changeStateMap_.emplace(MODE::FREE, std::bind(&Camera::ChangeModeFree, this));
	changeStateMap_.emplace(MODE::FIXED_POINT, std::bind(&Camera::ChangeModeFixedPoint, this));
	changeStateMap_.emplace(MODE::PLAYER_FOLLOW, std::bind(&Camera::ChangeModePlayerFollow, this));
	changeStateMap_.emplace(MODE::CAMERA_SCROLL, std::bind(&Camera::ChangeModeScroll, this));
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

	// カメラシェイク処理
	CameraShake();
}

void Camera::ChangeMode(const MODE mode)
{
	// カメラのモード
	mode_ = mode;

	// カメラ別モードの設定
	changeStateMap_.at(mode)();
}

void Camera::SetCameraShake(const float shakeTime, const float shakePower)
{
	shakeTime_ = shakeTime;
	shakePower_ = shakePower;
}

void Camera::SetCameraPosOffset()
{
	// オフセットを加算
	pos_ = Vector2F::AddVector2F(pos_, offset_);
}

void Camera::ResetCameraPos()
{
	// オフセットを減算
	pos_ = Vector2F::SubVector2F(pos_, offset_);
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
	pos_.y = (float)Application::SCREEN_SIZE_Y - 128 - followPos_->y;
}

void Camera::UpdateModeScroll()
{
	// リストの中が空の場合
	if (scrollMoves_.empty())
	{
		// 何もしない
		return;
	}

	// 現在目指すべき移動量を取得
	Vector2F& targetMove = scrollMoves_.front();

	// X軸の移動処理
	float moveX = 0.0f;
	if (targetMove.x > 0.0f)
	{
		moveX = (std::min)(SCROLL_SPEED, targetMove.x);
	}
	else if (targetMove.x < 0.0f)
	{
		moveX = (std::max)(-SCROLL_SPEED, targetMove.x);
	}

	// Y軸の移動処理
	float moveY = 0.0f;
	if (targetMove.y > 0.0f)
	{
		moveY = (std::min)(SCROLL_SPEED, targetMove.y);
	}
	else if (targetMove.y < 0.0f)
	{
		moveY = (std::max)(-SCROLL_SPEED, targetMove.y);
	}

	// カメラの座標に加算
	pos_.x -= moveX;
	pos_.y -= moveY;

	// 残りの移動量を減算
	targetMove.x -= moveX;
	targetMove.y -= moveY;

	// 移動し終えた場合
	if (targetMove.x == 0.0f && targetMove.y == 0.0f)
	{
		// 次の移動へ
		scrollMoves_.erase(scrollMoves_.begin());
	}
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

void Camera::ChangeModeScroll()
{
	updateFunction_ = std::bind(&Camera::UpdateModeScroll, this);
}

void Camera::CameraShake()
{
	// シェイク時間が残っていない場合はオフセットをリセットして終了
	if (shakeTime_ <= 0)
	{
		offset_ = {};
		return;
	}

	// ランダムな値を計算
	float randX = static_cast<float>(GetRand(static_cast<int>(shakePower_ * 200))) / 100.0f - shakePower_;
	float randY = static_cast<float>(GetRand(static_cast<int>(shakePower_ * 200))) / 100.0f - shakePower_;

	offset_.x = randX;
	offset_.y = randY;

	// 残り時間を減らす
	shakeTime_ -= scnMng_.GetDeltaTime();
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