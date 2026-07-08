#pragma once
#include "ComponentBase.h"

class Player;
class CollisionManager;

class ComponentCameraRangeCheck : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentCameraRangeCheck(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentCameraRangeCheck() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバッグ描画処理
	/// </summary>
	void DebugDraw() override;

private:

	// 所有者
	Player& owner_;

	// 衝突判定管理クラス
	CollisionManager& collisionManager_;

	// セーフエリア
	Vector2F safeAreaTop_;
	Vector2F safeAreaBottom_;
};