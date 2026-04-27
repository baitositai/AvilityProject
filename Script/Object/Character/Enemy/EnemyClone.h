#pragma once
#include "../CharacterBase.h"

class EnemyClone : public CharacterBase
{
public:

	struct Parameter : public CharacterBase::Parameter
	{
		Vector2F defaultAttackLocalPos = {};// 通常攻撃の当たり判定調整座標	
		float defaultAttackRadius = 0.0f;	// 通常攻撃の範囲半径

		// アニメーション関係
		int animationsIdle = -1;			// 待機アニメーション数
		int animationsWalk = -1;			// 移動アニメーション
		int animationsBrake = -1;			// ブレーキアニメーション
		int animationsAttack = -1;			// 攻撃アニメーション
		int animationsJump = -1;			// ジャンプアニメーション
		int animationsFall = -1;			// 落下アニメーション
		int animationsDie = -1;				// 死亡アニメーション
		int animationsDamage = -1;			// ダメージアニメーション
		int animationsPause = -1;			// ポーズアニメーション
		float animationAttackSpeed = 0.0f;	// 攻撃アニメーション速度
	};

	enum class ANIMATION
	{
		IDLE = 0,
		WALK = 1,
		BRAKE = 2,
		ATTACK = 3,
		JUMP = 4,
		FALL = 5,
		DIE = 6,
		DAMAGE = 7,
		PAUSE = 8,
		MAX
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="stateComponentNameList">状態別コンポーネントリスト</param>
	/// <param name="defaultComponentNameList">通常のコンポーネントリスト</param>
	EnemyClone(const Parameter& parameter, const std::unordered_map<std::string, std::string> stateComponentNameList, const std::vector<std::string> defaultComponentNameList = {});

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyClone() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void InitAnimation() override;

	/// <summary>
	/// アニメーション速度を攻撃用に変える
	/// </summary>
	void SetAttackAnimationSpeed() { parameterAnimation_.animationSpeed = parameter_.animationAttackSpeed; }

	/// <summary>
	/// アニメーションの変更
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="isLoop">ループ判定</param>
	void ChangeAnimation(const ANIMATION type, const bool isLoop = true);

private:

	// パラメータ情報
	Parameter parameter_;

};

