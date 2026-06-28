#pragma once
#include <vector>
#include <functional>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2.h"
#include "../../Collider/ColliderArray.h"

class ColliderBase;
class ColliderArray;

class CollisionManager : public Singleton<CollisionManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<CollisionManager>;

public:

	// 判定に必要なオブジェクトの情報
	struct CollisionCheckParam
	{
		Vector2 pos;
		Vector2 size;
		bool isXAxis;
		float stepMove;
	};

	// 判定結果を返す構造体
	struct CollisionResult
	{
		bool isHit;
		float chipSize;
		int chipIndex;
		Vector2F normal; // 反射に使う法線も一緒に返すと便利
	};
	
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
	/// ステージのコライダーのセット
	/// </summary>
	/// <param name="stageCollider">ステージのコライダー</param>
	void SetStageCollider(std::shared_ptr<ColliderArray> stageCollider) { stageCollider_ = stageCollider; }

	/// <summary>
	/// ステージとの衝突判定
	/// </summary>
	/// <param name="parameter">衝突判定のパラメータ情報</param>
	/// <returns>衝突判定結果</returns>
	CollisionResult CheckStageCollision(const CollisionCheckParam& parameter);

	/// <summary>
	/// 指定した座標がステージと衝突しているか調べる
	/// </summary>
	/// <param name="checkPos">調べたい座標</param>
	/// <returns>衝突している場合はtrue、それ以外はfalse</returns>
	ColliderArray::Result IsHitStage(const Vector2& checkPos);

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

	// ステージのコライダー
	std::shared_ptr<ColliderArray> stageCollider_;

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
	bool IsHitCheckCircleToFan(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckBoxToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckBoxToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckBoxToFan(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);
	bool IsHitCheckLineToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2);

	// コンストラクタ
	CollisionManager();

	// デストラクタ
	~CollisionManager();
};