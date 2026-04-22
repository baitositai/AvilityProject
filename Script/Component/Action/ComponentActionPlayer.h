#pragma once
#include "ComponentActionBase.h"
#include "../../Common/Vector2F.h"

class InputManager;
class Player;

class ComponentActionPlayer : public ComponentActionBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentActionPlayer(Player& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentActionPlayer() override;
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 入力管理クラスの参照
	InputManager& inputManager_;

	// 所有者
	Player& owner_;

	// 移動量
	Vector2F moveAmount_;

	// ジャンプ力
	float velocityY_;

	// 移動入力処理
	void ProcessInputMove();

	// ジャンプ入力処理
	void ProcessInputJump();

	// ジャンプによる移動量を計算
	void Jump();
};

