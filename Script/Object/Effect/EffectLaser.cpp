#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../OnHit/OnHitEffect.h"
#include "../../Object/ActorBase.h"
#include "EffectLaser.h"

EffectLaser::EffectLaser(std::unique_ptr<ParameterEffect> parameter, const Vector2F& direction, int cnt) :
	DIRECTION(direction),
	EffectBase(std::move(parameter))
{
	time_ = 0.0f;
	parameterEffect_ = GetParameterEffectPtr();

	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::AIRSLASH, parameterEffect_->pos_, parameterEffect_->hitRadius_);

	// 衝突後処理 ※コライダーは消したくないので、OnHitBaseを生成している
	onHit_ = std::make_unique<OnHitBase>(*this);

	if (cnt > 0)
	{
		cnt--;
		// 弾エフェクトのパラメータ設定
		std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();
		parameter->pos_ = Vector2F::AddVector2F(parameterEffect_->pos_, Vector2F::MulVector2FFloat(DIRECTION, 64.0f));
		parameter->gravityDir_ = parameterEffect_->gravityDir_;
		parameter->angle_ = parameterEffect_->angle_;
		parameter->hitRadius_ = 16.0f;
		parameter->resourceKey_ = "Leaser3";
		parameter->scale_ = 1.0f;
		parameter->divisionNum_ = { 9, 30 };
		parameter->transparent_ = true;
		parameter->moveSpeed_ = 0.0f;
		parameter->attackPower_ = parameterEffect_->attackPower_;
		parameter->attackBoostRate_ = parameterEffect_->attackBoostRate_;
		parameter->componentkeys_ = { "spriteAnimation" };
		parameter->animationDataMap_.emplace("effect", Animation::Data(9 * 20, 9 * 20 + 8, 0.1));
		// エフェクトの生成と追加
		std::unique_ptr<EffectLaser> effect = std::make_unique<EffectLaser>(std::move(parameter), DIRECTION, cnt);
		SpriteEffectManager::GetInstance().Add(std::move(effect));
	}
}

EffectLaser::~EffectLaser()
{
}

void EffectLaser::Init()
{
	// 基底クラスの初期化
	ActorBase::Init();

	// 再生
	animation_->Play(Animation::TYPE::EFFECT);
}

void EffectLaser::Update()
{
	//animation_->GetAnimationIndex();

	animation_->GetAnimationData().endIndex;

	// 移動量の更新
	parameterEffect_->pos_ = Vector2F::AddVector2F(
		parameterEffect_->pos_,
		Vector2F::MulVector2FFloat(DIRECTION, parameterEffect_->moveSpeed_));


	// 削除用カウント処理
	time_ += scnMng_.GetDeltaTime();

	if (animation_->GetAnimationIndex() >= 9 * 20 + 8 && time_ >= ALIVE_TIME)
	{
		Delete();
	}
	else if (animation_->GetAnimationIndex() >= (9 * 20 + 8 - 2)) {
		if (time_ <= ALIVE_TIME)
		{
			parameterEffect_->animationDataMap_.clear();
			parameterEffect_->animationDataMap_.emplace("effect", Animation::Data(9 * 20 + 2, 9 * 20 + 8 - 2, 0.1));
		}
		else
		{
			parameterEffect_->animationDataMap_.clear();
			parameterEffect_->animationDataMap_.emplace("effect", Animation::Data(9 * 20 + 2, 9 * 20 + 8, 0.1));
		}
		// アニメーション情報の格納
		for (auto& animation : parameterEffect_->animationDataMap_)
		{
			Animation::Data& animatioData = animation.second;
			animation_->Add(animation.first, animatioData.startIndex, animatioData.endIndex, animatioData.animationSpeed);
		}
	}

	// 基底クラスの処理
	ActorBase::Update();

}