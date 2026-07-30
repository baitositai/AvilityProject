#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Game/UiManager.h"
#include "../../Collider/ColliderBox.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Ui/Game/UiTrainTime.h"
#include "GimmickTrain.h"

GimmickTrain::GimmickTrain(std::unique_ptr<ParameterGimmickTrain> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterTrain_ = dynamic_cast<ParameterGimmickTrain*>(GetParameterGimmickPtr());
	assert(parameterTrain_ != nullptr);

	// 状態遷移処理の登録
	changeStateMap_.emplace(STATE::WAIT, std::bind(&GimmickTrain::ChangeStateWait, this));
	changeStateMap_.emplace(STATE::PASSING, std::bind(&GimmickTrain::ChangeStatePassing, this));

	// 初期情報
	state_ = STATE::MAX;
	timer_ = 0.0f;
	isCulling_ = false;
}

GimmickTrain::~GimmickTrain()
{
}

void GimmickTrain::Init()
{
	// コライダー
	parameterTrain_->hitSize_ = parameterTrain_->GetScaleToHitSize();
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::TRAIN, parameterTrain_->pos_, parameterTrain_->hitSize_, parameterTrain_->angle_);

	// 基底クラスの処理
	GimmickBase::Init();

	// 初期状態
	ChangeState(STATE::WAIT);

	// アニメーション再生
	animation_->Play(Animation::TYPE::WALK);
}

void GimmickTrain::Update()
{
	// 状態別更新処理
	update_();

	// 基底クラス処理
	GimmickBase::Update();
}

void GimmickTrain::Draw()
{
	if (isDraw_)
	{
		// 描画番号の付与
		parameterTrain_->drawIndex_ = static_cast<float>(animation_->GetAnimationIndex());
		ActorBase::Draw();
	}
}

void GimmickTrain::InitDraw()
{
	ActorBase::InitDraw();
}

void GimmickTrain::UpdateWait()
{
	// カメラが止まっている場合
	if (mainCamera.IsStop())
	{
		// 処理終了
		return;
	}

	// 時間更新
	timer_ -= scnMng_.GetDeltaTime();

	// 一定時間経った場合
	if (timer_ < 0.0f)
	{
		ChangeState(STATE::PASSING);
	}
}

void GimmickTrain::UpdatePassing()
{
	Vector2F screenTop = {}, screenBottom = { (float)Application::SCREEN_SIZE_X, (float)Application::SCREEN_SIZE_Y };
	Vector2F cameraPos = mainCamera.GetPos();

	// カメラ位置を減算
	screenTop = Vector2F::SubVector2F(screenTop, cameraPos);
	screenBottom = Vector2F::SubVector2F(screenBottom, cameraPos);

	// 画面外へ電車が通過した場合
	if (screenBottom.x < parameterTrain_->pos_.x - static_cast<float>(parameterTrain_->hitSize_.ToVector2F().x / 2))
	{
		// 待機
		ChangeState(STATE::WAIT);
		return;
	}

	// 移動処理
	parameterTrain_->pos_.x += parameterTrain_->moveSpeed_;
}

void GimmickTrain::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void GimmickTrain::ChangeStateWait()
{
	update_ = std::bind(&GimmickTrain::UpdateWait, this);

	// 描画判定無効
	isDraw_ = false;

	// 時間設定
	timer_ = static_cast<float>(UtilityCommon::GetRandomCount(parameterTrain_->waitTimeMax_, parameterTrain_->waitTimeMin_));

	// コライダー非活動状態
	collider_->SetIsActive(false);
}

void GimmickTrain::ChangeStatePassing()
{
	update_ = std::bind(&GimmickTrain::UpdatePassing, this);

	// 描画判定有効
	isDraw_ = true;

	// 電車初期位置
	Vector2F screenTop = Vector2F::SubVector2F(Vector2F(0.0f, (float)Application::SCREEN_SIZE_Y - 64.0f), mainCamera.GetPos());

	// 電車のハーフサイズ分オフセット
	parameterTrain_->pos_ = Vector2F::SubVector2F(screenTop, parameterTrain_->hitSize_.ToVector2F());

	// 効果音再生
	sndMng_.PlaySe(SoundType::SE::TRAIN_WHISTLE);

	// コライダー非活動状態
	collider_->SetIsActive(true);

	// UIの生成
	UiManager::GetInstance().Add(std::move(std::make_unique<UiTrainTime>()));
}