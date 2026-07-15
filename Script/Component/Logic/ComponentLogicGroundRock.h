#pragma once
#include "ComponentLogicBase.h"

class Camera;
class EnemyGaiaGolem;
class ParameterGimmick;
class ColliderCircle;
class ParameterEnemyGaiaGolem;

class ComponentLogicGroundRock :
    public ComponentLogicBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentLogicGroundRock(EnemyGaiaGolem& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentLogicGroundRock() override;

	/// <summary>
	/// 生成処理
	/// </summary>
	void Create() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 取り外し処理
	/// </summary>
	void Remove() override;

	/// <summary>
	/// 攻撃のリセット
	/// </summary>
	void AttackReset() override;

private:

	enum class STATE
	{
		ANIMATION,
		THROW_GROUNDROCKIT,
		END
	};

	//最小の岩の生成数
	static constexpr int ROCK_CREATE_NUM_MIN = 2;

	//カメラシェイク関連
	static constexpr int CAMERA_SHAKE_TIME = 0.2f;
	static constexpr int CAMERA_SHAKE_POWER = 6.0f;

	//岩座標のY固定座標
	static constexpr float ROCK_POS_Y = 180.0f;

	//岩サイズ
	static constexpr int ROCK_SIZE = 50;

	//ボス部屋の右端のX座標
	static constexpr int BOSS_ROOM_RIGHT_X = 128;

	//攻撃力
	static constexpr int ATTACK_POINT = 40;

	//GroundRock生成タイミングのアニメーションインデックス
	static constexpr int CREATE_GROUNDROCK_INDEX = 35;

	//速度横移動速度最大
	static constexpr float JUMP_SPD_MIN = 2.0f;
	static constexpr float JUMP_SPD_MID = 7.0f;
	static constexpr float JUMP_SPD_MAX = 15.0f;

	// 所有者
	EnemyGaiaGolem& owner_;

	//カメラ
	Camera& camera_;

	// 所有者のパラメータ
	ParameterEnemyGaiaGolem& parameter_;

	// 攻撃コライダー
	std::shared_ptr<ColliderCircle> attackCollider_;

	//近接攻撃の座標
	Vector2F attackPos_;

	//GroundRockを生成フラグ
	bool isCreateGroundRock_;

	//GroundRockの生成
	void CreateGroundRock(void);

	//水平方向の速度をランダムに決める
	float SetRandomHorizonSpd(std::array<int, ROCK_CREATE_NUM_MIN>&_horizonSpd,const int _createIndex );
};

