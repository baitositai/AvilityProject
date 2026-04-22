#pragma once
#include "ComponentAvilityBase.h"
#include "../../Common/Vector2F.h"

class InputManager;
class Player;

class AvilityShot :
    public ComponentAvilityBase
{
public:

	static constexpr float SHOT_INTERVAL = 0.5f;	// ショットのインターバル
	static constexpr float SHOT_SPEED = 15.0f;		// ショットの速度

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	AvilityShot(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AvilityShot() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 入力管理クラスの参照
	InputManager& inputManager_;

	// 移動量
	Vector2F moveAmount_;

	// 移動入力処理
	void ProcessInputShot();
	void ProcessMoveShot();

	// 状態関数マップ
	std::unordered_map<std::string, std::function<void(void)>> stateFunctionMap_;
	// 現在の状態
	std::string currentState_;
	std::function<void(void)> currentStateFunction_;

	// ショット変数
	float shotCount_;
	Vector2F shotVec_;

};

