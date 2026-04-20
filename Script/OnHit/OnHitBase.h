#pragma once
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include "../Manager/Game/CollisionTags.h"

class ActorBase;
class ColliderBase;

class OnHitBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitBase(ActorBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~OnHitBase();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="opponentCollider">衝突相手</param>
	virtual void Update(const std::weak_ptr<ColliderBase>& opponentCollider);

protected:

	// 衝突後処理
	void OnHitNone(const std::weak_ptr<ColliderBase>& opponentCollider) {};

	//衝突後の処理を管理するマップ
	std::unordered_map<CollisionTags::TAG, std::function<void(const std::weak_ptr<ColliderBase>&)>> onHitMap_;
};

