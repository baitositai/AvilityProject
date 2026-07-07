#pragma once
#include "ComponentCharacterStateBase.h"

class Player;
class ParameterPlayer;
class ColliderCircle;
class InputManager;

class ComponentStatePlayerAttack : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerAttack(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerAttack() override;

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

private:

	// 攻撃開始フレーム
	const int ATTACK_START_FRAME;
	const int ATTACK_SECOND_FRAME;

	// 通常攻撃の相対位置
	const float ATTACK_DISTANCE;

	// 所有者
	Player& owner_;

	// パラメータ
	ParameterPlayer& parameter_;

	// 入力管理クラス
	InputManager& inputManager_;

	// 攻撃位置
	Vector2F attackPos_;

	// 攻撃開始
	bool isAttack_;
	bool isAttackSecond_;
	bool isInputAttackSecond_;

	// 攻撃コライダー
	std::shared_ptr<ColliderCircle> collider_;

	// 攻撃終了
	void AttackEnd();
};