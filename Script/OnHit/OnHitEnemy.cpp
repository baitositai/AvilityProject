#include "../../Collider/ColliderBase.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "OnHitEnemy.h"

OnHitEnemy::OnHitEnemy(EnemyBase& owner):
	owner_(owner),
	OnHitCharacterBase(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_ATTACK_NORMAL, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_AVILITY_STAMP, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAvilityStamp(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_AVILITY_SHOT, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::AIRSLASH, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::TELEPORT_EXIT, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitOtherEnemy(opponentCollider);
		});
}

OnHitEnemy::~OnHitEnemy()
{
}

void OnHitEnemy::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 自身のタグ別に処理を呼び分ける
    switch (opponentCollider.lock()->GetPartnerTag())
    {
    case CollisionTags::TAG::ENEMY_CLONE:
		// 基底クラスの共通処理
        OnHitCharacterBase::Update(opponentCollider);
        break;

    case CollisionTags::TAG::ENEMY_VIEW:
        // 現状プレイヤーだけ
        OnHitEnemyViewToPlayer(opponentCollider);
        break;

    default:
        break;
    }
}

void OnHitEnemy::OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{        
    // 攻撃を無効
    owner_.AttackReset();
	
    // 衝突者が無敵のときは無視
    if (owner_.IsInvincible()
        || opponentCollider.lock()->GetPartnerTag() == CollisionTags::TAG::PLAYER_ATTACK_NORMAL
        || opponentCollider.lock()->GetPartnerTag() == CollisionTags::TAG::PLAYER_AVILITY_SHOT
        )
    {
        return;
    }

    // ダメージ処理
    Damage(opponentCollider);

	// 相手コライダーの判定を無効化
	opponentCollider.lock()->SetIsActive(false);
}

void OnHitEnemy::OnHitPlayerAvilityStamp(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// ノックバック処理
	KnockBack(opponentCollider, KNOCK_BACK_FORCE);

	// 相手コライダーの判定を無効化
	opponentCollider.lock()->SetIsActive(false);
}

void OnHitEnemy::OnHitOtherEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    return;
    auto pinOpponent = opponentCollider.lock();
    if (pinOpponent == nullptr)
    {
        return;
    }

    // 自身のパラメータを参照で取得
    auto& myParam = owner_.GetParameter();

    // 自身の中心座標と、コライダーのサイズ（幅・高さ）を取得
    Vector2F myPos = myParam.pos_;
    Vector2F mySize = myParam.hitSize_.ToVector2F();
    float myHalfW = mySize.x * 0.5f;
    float myHalfH = mySize.y * 0.5f;

    // 相手の中心座標とサイズを取得
    // ※もし相手の位置もColliderBaseから取れる場合はそこから、
    // あるいは相手のOwnerから取得してください。ここでは仮にColliderから取得とします。
    Vector2F opponentPos = pinOpponent->GetPos();
    Vector2 temp = pinOpponent->GetOwner().GetParameter().hitSize_;
	Vector2F opponentSize = temp.ToVector2F();
    float opponentHalfW = opponentSize.x * 0.5f;
    float opponentHalfH = opponentSize.y * 0.5f;

    // 2つの四角形の中心点間の距離（差分）
    float dx = opponentPos.x - myPos.x;
    float dy = opponentPos.y - myPos.y;

    // 衝突（重なり）しているとみなされる基準距離（お互いの半分の長さの和）
    float minDistanceX = myHalfW + opponentHalfW;
    float minDistanceY = myHalfH + opponentHalfH;

    // 各軸の「重なり（侵入深度）」を計算（絶対値から引く）
    float overlapX = minDistanceX - fabsf(dx);
    float overlapY = minDistanceY - fabsf(dy);

    // 両方の軸で重なりが正（プラス）であれば衝突している
    if (overlapX > 0.0f && overlapY > 0.0f)
    {
        // 重なりが少ない方の軸で押し戻す（その方が移動量が少なく済むため）
        if (overlapX < overlapY)
        {
            // X軸方向の押し戻し
            // 相手が右にいれば自分は左に、相手が左にいれば自分は右に退く
            float signX = (dx > 0.0f) ? 1.0f : -1.0f;

            // 互いに半分ずつ押し戻し合う（自分は相手と逆方向へ）
            float separateX = signX * overlapX * 0.5f;

            myParam.pos_.x -= separateX;
        }
        else
        {
            // Y軸方向の押し戻し
            // 相手が下にいれば自分は上に、相手が上にいれば自分は下に退く
            float signY = (dy > 0.0f) ? 1.0f : -1.0f;

            // 互いに半分ずつ押し戻し合う
            float separateY = signY * overlapY * 0.5f;

            myParam.pos_.y -= separateY;
        }
    }
}

void OnHitEnemy::OnHitEnemyViewToPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // ターゲットを発見
	owner_.GetParameter().isDiscover_ = true;

    // ターゲットの座標を設定
	owner_.GetParameter().targetPos_ = &opponentCollider.lock()->GetPos();
}
