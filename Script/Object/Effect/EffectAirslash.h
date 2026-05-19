#pragma once
#include "EffectBase.h"

class EffectAirslash : public EffectBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="direction">方向</param>
	EffectAirslash(const Vector2F& direction);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EffectAirslash() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 生存時間
	static constexpr float ALIVE_TIME = 2.0f;

	// 方向
	const Vector2F& direction_;

	// 時間
	float time_;
};

