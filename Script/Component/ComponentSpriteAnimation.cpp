#include "../Object/ActorBase.h"
#include "../Object/Common/Animation.h"
#include "ComponentSpriteAnimation.h"

ComponentSpriteAnimation::ComponentSpriteAnimation(ActorBase& owner) :
	ComponentBase(owner),
	animation_(owner_.GetAnimation())
{
	animStep_ = 0.0f;
	animationPreType_ = -1;
}

ComponentSpriteAnimation::~ComponentSpriteAnimation()
{
}

void ComponentSpriteAnimation::Update()
{
	// アニメーションが非再生の場合
	if (!animation_.IsPlay()) { return; }

	// アニメーション情報の取得
	const Animation::Data& data = animation_.GetAnimationData();

	// アニメーション終了かつループを行わない場合
	if (animation_.GetAnimationIndex() == data.endIndex && !animation_.IsLoop())
	{
		animStep_ = 0.0f;					// 初期化
		animation_.Stop();					// 停止
		animation_.CheckNextAnimation();		// 次回アニメーションの確認
		return;								// 処理終了
	}

	// 前回のアニメーションと現在のアニメーションが異なる場合
	if (static_cast<int>(animation_.GetType()) != animationPreType_)
	{
		// アニメーションステップ初期化
		animStep_ = 0.0f;
	}

	// バックアップを取得
	animationPreType_ = static_cast<int>(animation_.GetType());

	//ステップ更新
	animStep_ += data.animationSpeed;

	//アニメーション最大値を入手
	int animMax = data.endIndex - data.startIndex + 1;

	//アニメーション番号の割り当て
	animation_.SetAnimationIndex(data.startIndex + static_cast<int>(animStep_) % animMax);
}