#pragma once
#include "EffectBase.h"
class EffectLaser :
    public EffectBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="direction">方向</param>
	EffectLaser(std::unique_ptr<ParameterEffect> parameter, const Vector2F& direction,int cnt);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EffectLaser() override;

	/// <summary>
	/// 初期化処理
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
	const Vector2F DIRECTION;

	// パラメータ情報
	ParameterEffect* parameterEffect_;

	// 時間
	float time_;
};

