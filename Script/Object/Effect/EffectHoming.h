#pragma once
#include "EffectBase.h"

class Player;

class EffectHoming : public EffectBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="direction">方向</param>
	EffectHoming(std::unique_ptr<ParameterEffect> parameter, const Vector2F& pos, const Player& target);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EffectHoming() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 寿命
	static constexpr float LIFE_TIME = 5.0f;

	// 移動速度
	static constexpr float MOVE_SPEED = 300.0f;

	// 旋回速度
	static constexpr float TURN_SPEED = 5.0f;

	// パラメータ情報
	ParameterEffect* parameterEffect_;

	// 追尾対象
	const Player& target_;

	// 移動方向
	Vector2F direction_;

	// 経過時間
	float timer_ = 0.0f;
};