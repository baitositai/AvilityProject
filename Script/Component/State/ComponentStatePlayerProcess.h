#pragma once
#include "ComponentCharacterStateBase.h"
#include "../Common/Vector2F.h"

class InputManager;
class Player;
class ParameterPlayer;

class ComponentStatePlayerProcess : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerProcess(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerProcess() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 入力管理クラスの参照
	InputManager& inputManager_;

	// 所有者
	Player& owner_;

	// パラメータ
	ParameterPlayer& parameter_;

	// 移動量
	Vector2F moveAmount_;

	// ジャンプ力
	float velocityY_;

	// 地面判定
	bool isGround_;

	// 移動入力処理
	void ProcessInputMove();

	// ジャンプ入力処理
	void ProcessInputJump();

	// 攻撃入力処理
	void ProcessInputAttack();
};