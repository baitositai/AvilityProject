#pragma once
#include "ComponentBase.h"

class Animation;

class ComponentSpriteAnimation : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentSpriteAnimation(ActorBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentSpriteAnimation() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 所有者のアニメーション
	Animation& animation_;

	//アニメーションステップ
	float animStep_;

	// アニメーション種類のバックアップ
	int animationPreType_;
};