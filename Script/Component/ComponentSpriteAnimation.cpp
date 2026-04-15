#include "../Object/ActorBase.h"
#include "ComponentSpriteAnimation.h"

ComponentSpriteAnimation::ComponentSpriteAnimation(ActorBase& owner) :
	ComponentBase(&owner)
{
	animStep_ = 0.0f;
}

ComponentSpriteAnimation::~ComponentSpriteAnimation()
{
}

void ComponentSpriteAnimation::Update()
{
	// アニメーション情報の取得
	ActorBase::ParameterAnimation parameterAnimation = owner_->GetParameterAnimation();

	//アニメーションが非再生の場合
	if (!parameterAnimation.isPlay) { return; }

	//アニメーション終了かつループを行わない場合
	if (parameterAnimation.animationIndex == parameterAnimation.animationFinishIndex && !parameterAnimation.isLoop)
	{
		parameterAnimation.isPlay = false;	//再生しない
		animStep_ = 0.0f;	//初期化
		return;				//処理終了
	}

	//ステップ更新
	animStep_ += parameterAnimation.animationSpeed;

	//アニメーション最大値を入手
	int animMax = parameterAnimation.animationFinishIndex + 1 - parameterAnimation.animationStartIndex;

	//アニメーション番号の割り当て
	parameterAnimation.animationIndex = parameterAnimation.animationStartIndex + static_cast<int>(animStep_) % animMax;

	// アニメーション情報の更新
	owner_->SetAnimationIndex(parameterAnimation.animationIndex);
}