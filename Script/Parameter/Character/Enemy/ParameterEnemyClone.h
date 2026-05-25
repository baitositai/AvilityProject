#pragma once
#include "../ParameterCharacter.h"

class ParameterEnemyClone :  public ParameterCharacter
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEnemyClone();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEnemyClone() override;

	/// <summary>
	/// パラメータの読み込み
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	void LoadParameter(const Json& parameter) override;

	// アニメーション関係
	int animationsIdle_ = -1;			// 待機アニメーション数
	int animationsWalk_ = -1;			// 移動アニメーション
	int animationsBrake_ = -1;			// ブレーキアニメーション
	int animationsAttack_ = -1;			// 攻撃アニメーション
	int animationsJump_ = -1;			// ジャンプアニメーション
	int animationsFall_ = -1;			// 落下アニメーション
	int animationsDie_ = -1;			// 死亡アニメーション
	int animationsDamage_ = -1;			// ダメージアニメーション
	int animationsPause_ = -1;			// ポーズアニメーション
	float animationAttackSpeed_ = 0.0f;	// 攻撃アニメーション速度
};

