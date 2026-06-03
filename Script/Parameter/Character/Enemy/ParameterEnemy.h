#pragma once
#include "../ParameterCharacter.h"

class ParameterEnemy : public ParameterCharacter
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEnemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterEnemy() override;

    /// <summary>
	/// 外部データの読み込み
	/// </summary>
	/// <param name="parameter">読み込むJSONデータ</param>
    virtual void LoadParameter(const Json& parameter) override;

	// ターゲット座標
	const Vector2F* targetPos_;

	// 目的地
	Vector2F goalPos_;

	// ターゲットの発見判定
	bool isDiscover_;	

	// 視野角度
	float eyeAngle_;

	// 視野角度のラジアン値
	float eyeAngleRad_;

	// 視野距離
	float eyeDistance_;

	// 攻撃を開始する距離
	float attackStartDistance_;

	// 許容距離
	float permissibleDistance_;
};