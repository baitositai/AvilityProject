#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Collider/ColliderCircle.h"
#include "../../OnHit/OnHitTarget.h"
#include "GimmickTarget.h"

GimmickTarget::GimmickTarget(std::unique_ptr<ParameterGimmickTarget> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterTarget_ = dynamic_cast<ParameterGimmickTarget*>(GetParameterGimmickPtr());
	assert(parameterTarget_ != nullptr);
}

GimmickTarget::~GimmickTarget()
{
}

void GimmickTarget::Init()
{
	// コライダー
	collider_ = std::make_unique<ColliderCircle>(*this, CollisionTags::TAG::TARGET, parameterTarget_->pos_, parameterTarget_->hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitTarget>(*this);

	// 基底クラスの処理
	ActorBase::Init();
}

void GimmickTarget::Update()
{
	// 移動する場合
	if (parameterTarget_->isMove_)
	{
		// カメラ外に出そうな場合
		if (CheckCameraRange() || IsCheckPrePos())
		{
			// 反転
			parameterTarget_->moveSpeed_ *= -1.0f;
		}		
		
		// バックアップ座標を取得
		prePos_ = parameterTarget_->pos_;

		// 移動処理
		parameterTarget_->moveAmount_ = Vector2F::MulVector2FFloat(parameterTarget_->moveDir_, parameterTarget_->moveSpeed_);

		// 基底クラスの処理
		ActorBase::Update();
	}
}

bool GimmickTarget::CheckCameraRange()
{
	// カメラ座標を取得
	const Vector2F cameraPos = mainCamera.GetPos();

	// セーフエリアの定義
	Vector2F safeAreaTop = { 0, 0 };
	Vector2F safeAreaBottom = { (float)Application::SCREEN_SIZE_X, (float)Application::SCREEN_SIZE_Y };

	// カメラ座標を足す
	safeAreaTop = Vector2F::SubVector2F(safeAreaTop, cameraPos);
	safeAreaBottom = Vector2F::SubVector2F(safeAreaBottom, cameraPos);

	// カメラ範囲か判定
	if (safeAreaTop.x >= parameterTarget_->pos_.x - parameterTarget_->hitRadius_ ||
		safeAreaTop.y >= parameterTarget_->pos_.y - parameterTarget_->hitRadius_ ||
		safeAreaBottom.x <= parameterTarget_->pos_.x + parameterTarget_->hitRadius_ ||
		safeAreaBottom.y <= parameterTarget_->pos_.y + parameterTarget_->hitRadius_)
	{
		return true;
	}
	return false;
}

bool GimmickTarget::IsCheckPrePos()
{
	constexpr float TOLERANCE = 0.5f;
	const Vector2F& pos = parameterTarget_->pos_;
	if (pos.x <= prePos_.x + TOLERANCE &&
		pos.x >= prePos_.x - TOLERANCE &&
		pos.y <= prePos_.y + TOLERANCE &&
		pos.y >= prePos_.y - TOLERANCE)
	{
		return true;
	}
	return false;
}
