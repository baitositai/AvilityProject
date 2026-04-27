#pragma once
#include <memory>
#include "../Manager/Game/CollisionTags.h"
#include "../Common/Vector2F.h"
#include "ColliderType.h"

class ActorBase;

class ColliderBase
{
public: 

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">衝突判定タグ</param>
	/// <param name="followPos">追従対象</param>
	ColliderBase(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ColliderBase();

	/// <summary>
	/// 衝突後の処理
	/// </summary>
	/// <param name="opponentCollider">衝突相手のコライダー</param>
	void OnHit(const std::weak_ptr<ColliderBase>& opponentCollider);

	/// <summary>
	/// 衝突してるか返す
	/// </summary>
	/// <returns>衝突していたらtrue,してない場合false</returns>
	const bool IsHit() const { return isHit_; }

	/// <summary>
	/// 削除判定
	/// </summary>
	/// <returns>削除する場合true,そうでない場合false</returns>
	const bool IsDelete() const { return isDelete_; }

	/// <summary>
	/// 活動判定を返す
	/// </summary>
	/// <returns>活動判定</returns>
	const bool IsActive() const { return isActive_; }

	/// <summary>
	/// 削除設定
	/// </summary>
	void SetDelete() { isDelete_ = true; }

	/// <summary>
	/// 活動判定を格納
	/// </summary>
	/// <param name="isActive">活動判定</param>
	void SetIsActive(const bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// 自身のコライダー種類を返す
	/// </summary>
	/// <returns>種類</returns>
	const ColliderType::TYPE GetType() const { return type_; }

	/// <summary>
	/// 自身の衝突物の種類を返す
	/// </summary>
	/// <returns>衝突物の種類</returns>
	const CollisionTags::TAG GetTag() const { return tag_; }

	/// <summary>
	/// 衝突相手の種類を返す
	/// </summary>
	/// <returns>相手の衝突物の種類</returns>
	const CollisionTags::TAG GetPartnerTag() const { return partnerTag_; }

	/// <summary>
	/// 所有者のインスタンスを返す
	/// </summary>
	/// <returns>所有者のインスタンス</returns>
	const ActorBase& GetOwner() const { return owner_; }

	/// <summary>
	/// 追従対象の座標を渡す
	/// </summary>
	/// <returns>追従対象の座標</returns>
	const Vector2F& GetPos() const { return followPos_; }

	/// <summary>
	/// 衝突相手の種類を設定
	/// </summary>
	/// <param name="partnerTag"></param>
	void SetPertnerTag(const CollisionTags::TAG partnerTag) { partnerTag_ = partnerTag; }

	/// <summary>
	/// 衝突タグの変更
	/// </summary>
	void ChangeTag(const CollisionTags::TAG changeTag) { tag_ = changeTag; }

	/// <summary>
	/// 自身の複製を生成
	/// </summary>
	/// <returns>複製したインスタンス</returns>
	virtual std::shared_ptr<ColliderBase> Clone() const = 0;

	/// <summary>
	/// デバッグの描画
	/// </summary>
	virtual void DebugDraw();

protected:		
	
	// オーナー
	ActorBase& owner_;

	// 追従対象
	Vector2F& followPos_;
	
	// タグ
	CollisionTags::TAG tag_;

	// 相手の衝突物種類
	CollisionTags::TAG partnerTag_;

	// 自身のコライダー種類
	ColliderType::TYPE type_;

	//衝突判定
	bool isHit_;

	// 削除判定
	bool isDelete_;

	// 活動判定
	bool isActive_;
};