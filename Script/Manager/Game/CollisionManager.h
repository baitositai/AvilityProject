#pragma once
#include <vector>
#include <functional>
#include "../../Template/Singleton.h"

class ColliderBase;

class CollisionManager : public Singleton<CollisionManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<CollisionManager>;

public:
	
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// コライダーの追加
	/// </summary>
	/// <param name="collider">コライダー</param>
	void Add(std::shared_ptr<ColliderBase> collider);

	/// <summary>
	/// 削除
	/// </summary>
	void Clear();

	/// <summary>
	/// 不要のコライダーの削除
	/// </summary>
	void Sweep();

private:

	// 衝突用タグのマトリックス
	std::vector<std::vector<bool>> collTagMatrix_;

	// 衝突判定処理用のマトリックス
	std::vector<std::vector<std::function<bool(std::weak_ptr<ColliderBase>, std::weak_ptr<ColliderBase>)>>> collisionFunctionMatrix_;

	// コライダー配列
	std::vector<std::shared_ptr<ColliderBase>> colliders_;

		// タグのマトリックスの設定設定
	void InitTagMatrix();

	// コライダー種のマトリックス設定
	void InitColliderMatrix();

	// 各種類ごとの衝突判定
	bool IsHitCheckArrayToCircle(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckArrayToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckCircleToCircle(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckCircleToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckCircleToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckBoxToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckBoxToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckLineToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);

	// コンストラクタ
	CollisionManager();

	// デストラクタ
	~CollisionManager();

};
