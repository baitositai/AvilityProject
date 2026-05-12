#pragma once
#include "ComponentBase.h"
#include "../Common/Vector2F.h"
#include "../Common/Vector2.h"
#include "../../Object/ActorBase.h"

class CollisionManager;

class ComponentMove : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentMove(ActorBase& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentMove() override;
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 衝突管理クラス
	CollisionManager& collisionManager_;

	// 移動量
	Vector2F moveAmount_;

	// 座標
	Vector2F pos_;

	// サイズ
	Vector2 defaultSize_;	// 通常
	Vector2 nowSize_;		// 現在

	// 重力方向
	ActorBase::DIR gravityDir_;

	// 衝突判定と押し出し処理の共通ロジック
	void ProcessCollision(bool isXAxis);

	// 接地判定の共通ロジック
	void CheckGroundStatus(float moveVal, bool isXAxis);
};

