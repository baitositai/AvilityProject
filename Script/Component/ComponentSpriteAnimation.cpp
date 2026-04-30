#include "../Object/ActorBase.h"
#include "../Object/Common/Animation.h"
#include "ComponentSpriteAnimation.h"

ComponentSpriteAnimation::ComponentSpriteAnimation(ActorBase& owner) :
	ComponentBase(&owner)
{
	animStep_ = 0.0f;
	animationPreType_ = -1;
}

ComponentSpriteAnimation::~ComponentSpriteAnimation()
{
}

void ComponentSpriteAnimation::Update()
{
	// アニメーション情報の取得
	Animation& animation = owner_->GetAnimation();

	// アニメーションが非再生の場合
	if (!animation.IsPlay()) { return; }

	// アニメーション情報の取得
	const Animation::Data& data = animation.GetAnimationData();

	// アニメーション終了かつループを行わない場合
	if (animation.GetAnimationIndex() == data.endIndex && !animation.IsLoop())
	{
		animStep_ = 0.0f;					// 初期化
		animation.Stop();					// 停止
		animation.CheckNextAnimation();		// 次回アニメーションの確認
		return;								// 処理終了
	}

	// 前回のアニメーションと現在のアニメーションが異なる場合
	if (static_cast<int>(animation.GetType()) != animationPreType_)
	{
		// アニメーションステップ初期化
		animStep_ = 0.0f;
	}

	// バックアップを取得
	animationPreType_ = static_cast<int>(animation.GetType());

	//ステップ更新
	animStep_ += data.animationSpeed;

	//アニメーション最大値を入手
	int animMax = data.endIndex - data.startIndex + 1;

	//アニメーション番号の割り当て
	animation.SetAnimationIndex(data.startIndex + static_cast<int>(animStep_) % animMax);
}