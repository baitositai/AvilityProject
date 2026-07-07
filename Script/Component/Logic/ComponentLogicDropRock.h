#pragma once
#include "ComponentLogicBase.h"

class EnemyGaiaGolem;
class ParameterGimmick;
class ColliderCircle;
class ParameterEnemyGaiaGolem;

class ComponentLogicDropRock :
    public ComponentLogicBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ComponentLogicDropRock(EnemyGaiaGolem& owner);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ComponentLogicDropRock();

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
		NONE,
		WAIT,
		DROP,
		END
	};

	//最小の岩の生成数
	static constexpr int ROCK_CREATE_NUM_MIN = 3;

	//岩座標のY固定座標
	static constexpr float ROCK_POS_Y = 100.0f;

	//岩サイズ
	static constexpr int ROCK_SIZE = 80;

	//岩生成の範囲


	// 所有者
	EnemyGaiaGolem& owner_;

	// 所有者のパラメータ
	ParameterEnemyGaiaGolem& parameter_;

	//ランダムに岩のY座標を決める(X座標は固定)
	float SetRandomPosX(void);

	////岩のパラメータ(基本パラメータしか使用しない)
	//std::list<std::unique_ptr<ParameterGimmick>> gimmickParameters_;
};

