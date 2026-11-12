#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../OnHit/OnHitEffect.h"
#include "../Character/Player.h"
#include "EffectHoming.h"

EffectHoming::EffectHoming(std::unique_ptr<ParameterEffect> parameter, const Vector2F& pos, const Player& target) :
	EffectBase(std::move(parameter)),
	target_(target)
{

	parameterEffect_->pos_ = pos;	

	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, parameterEffect_->tag_, parameterEffect_->pos_, parameterEffect_->hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEffect>(*this);
}

EffectHoming::~EffectHoming()
{
}

void EffectHoming::Init()
{
	// 基底クラスの初期化
	ActorBase::Init();
}

void EffectHoming::Update()
{
	const float deltaTime = SceneManager::GetInstance().GetDeltaTime();

	// 寿命を超えたら削除
	timer_ += deltaTime;
	if (timer_ >= LIFE_TIME)
	{
		Delete();
		return;
	}

	// プレイヤーへの方向を取得
	Vector2F targetDirection = target_.GetParameter().pos_;
	targetDirection.x -= parameterEffect_->pos_.x;
	targetDirection.y -= parameterEffect_->pos_.y;
	targetDirection.Normalize();

	// 徐々にプレイヤーの方向へ旋回
	direction_.x += (targetDirection.x - direction_.x) * TURN_SPEED * deltaTime;
	direction_.y += (targetDirection.y - direction_.y) * TURN_SPEED * deltaTime;
	direction_.Normalize();

	// 移動
	parameterEffect_->pos_.x += direction_.x * MOVE_SPEED * deltaTime;
	parameterEffect_->pos_.y += direction_.y * MOVE_SPEED * deltaTime;
	// コライダーの位置を更新
	//collider_->Se(parameterEffect_->pos_);
}
