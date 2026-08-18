#pragma once
#include "../ParameterCharacter.h"

class ParameterEnemy : public ParameterCharacter
{
public:

	// 敵の移動タイプ
	enum class HABITAT_TYPE
	{
		LAND,	// 陸
		AIR,		// 空中
		MAX
	};

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

	// 攻撃の遅延時間
	float attackDelayTime_;

	// 生成率
	float spawnRate_;

	// ロジックの遅延
	float logicDelay_;

	// ショットダメージ用インターバル
	float shotDamageInterval_;

	// 落とす金額
	int dropMoney_;

	// 各攻撃の開始フレーム
	int defaultAttackStartFrame2_;
	int defaultAttackStartFrame3_;
	int defaultAttackStartFrame4_;

	// アウトラインの倍率
	float outLineRate_;

	// 移動種類
	HABITAT_TYPE habitatType_;

	// ロジックマップ
	std::unordered_map<std::string, float> logicMap_;

private:

	// 移動種類を列挙型に変換
	const std::unordered_map<std::string, HABITAT_TYPE> HABITAT_TYPE_STRING_TO_ENUM = {
		{ "land", HABITAT_TYPE::LAND },
		{ "air", HABITAT_TYPE::AIR }
	};
};