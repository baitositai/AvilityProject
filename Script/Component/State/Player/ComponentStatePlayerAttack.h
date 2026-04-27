#pragma once
#include "../ComponentCharacterStateBase.h"
#include "../Common/Vector2F.h"

class Player;
class ColliderCircle;

class ComponentStatePlayerAttack : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerAttack(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerAttack() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 通常攻撃の相対位置
	const Vector2F DEFAULT_ATTACK_LOCAL_POS;

	// 所有者
	Player& owner_;

	// 攻撃位置
	Vector2F attackPos_;

	// 攻撃開始
	bool isAttack_;

	std::shared_ptr<ColliderCircle> collider_;
};

