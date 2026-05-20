#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include "ComponentAvilityBase.h"
#include "../../Common/Vector2F.h"

class Player;
class ColliderBox;

class ComponentAvilityShot :  public ComponentAvilityBase
{
public:

	static constexpr float SHOT_INTERVAL = 0.5f;	// ショットのインターバル
	static constexpr float SHOT_SPEED = 15.0f;		// ショットの速度

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityShot(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityShot() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 取り外し時の処理
	/// </summary>
	void Remove() override;

private:

	// 衝突管理クラス
	CollisionManager& collisionManager_;

	// 入力管理クラスの参照
	InputManager& inputManager_;

	// 移動量
	Vector2F moveAmount_;

	// 座標
	Vector2F pos_;

	// サイズ
	Vector2 defaultSize_;	// 通常
	Vector2 nowSize_;		// 現在

	// 重力方向
	ParameterActor::DIR gravityDir_;

	// 攻撃判定用コライダー
	std::shared_ptr<ColliderBox> attackCollider_;

	// 移動入力処理
	void ProcessInputShot();
	void ProcessInputCharge();
	void ProcessMoveShot();

	// 衝突処理
	void ProcessCollision(bool isXAxis);
	void CheckGroundStatus(float moveVal, bool isXAxis);

	// 状態関数マップ
	std::unordered_map<std::string, std::function<void(void)>> stateFunctionMap_;
	// 現在の状態
	std::string currentState_;
	std::function<void(void)> currentStateFunction_;

	// 反射回数
	bool isReflected_;
	int reflectCount_;

	// ショット変数
	float chageTime_;
	float shotTime_;
	Vector2F shotVec_;
	float shotAngle_;

};