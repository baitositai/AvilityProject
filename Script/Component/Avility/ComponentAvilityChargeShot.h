#pragma once
#include <functional>
#include "ComponentAvilityBase.h"
#include "../../Common/Vector2F.h"


class InputManager;
class Player;

class ComponentAvilityChargeShot :
    public ComponentAvilityBase
{
public:

	static constexpr float SHOT_INTERVAL = 0.5f;	// ショットのインターバル
	static constexpr float SHOT_SPEED = 15.0f;		// ショットの速度

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityChargeShot(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityChargeShot() override;

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
	void ProcessInputCharge();
	void ProcessMoveShot();

	// 状態関数マップ
	std::unordered_map<std::string, std::function<void(void)>> stateFunctionMap_;
	// 現在の状態
	std::string currentState_;
	std::function<void(void)> currentStateFunction_;

	// ショット変数
	float chageTime_;
	float shotTime_;
	Vector2F shotVec_;

};

