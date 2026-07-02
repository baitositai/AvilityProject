#include "../../Utility/Utility2D.h"
#include "../../Object/Character/Enemy/EnemyPanda.h"
#include "../../Object/Common/Animation.h"
#include "../../Collider/ColliderBase.h"
#include "OnHitEnemyPanda.h"

OnHitEnemyPanda::OnHitEnemyPanda(EnemyPanda& owner) :
	OnHitEnemy(owner),
	owner_(owner)
{
}

OnHitEnemyPanda::~OnHitEnemyPanda()
{
}

void OnHitEnemyPanda::OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 自身のパラメータ
	auto& parameter = owner_.GetParameter();

	// 衝突位置が自身より前方向の場合
	Vector2 hitPos = opponentCollider.lock()->GetHitPos();
	Vector2 myPos = parameter.pos_.ToVector2();
	Vector2F frontDir = parameter.GetFront();

	// 敵から見た攻撃位置への方向ベクトルを計算
	Vector2F toHitVec = Vector2::SubVector2(hitPos, myPos).ToVector2F();

	// 内積を計算
	float dot = Utility2D::Dot(toHitVec, frontDir);

	// 内積がプラスであれば前方向からの攻撃
	if (dot > 0.0f)
	{
		// 防御処理
		owner_.Defence();
	}
	else
	{
		// シンプルにダメージ
		OnHitEnemy::OnHitPlayerAttack(opponentCollider);
	}
}
