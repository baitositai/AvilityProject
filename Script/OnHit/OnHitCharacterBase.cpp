#include <algorithm>
#include "../Utility/UtilityCommon.h"
#include "../Utility/Utility2D.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "../Object/ActorBase.h"
#include "../Object/Common/Animation.h"
#include "../Object/Character/CharacterBase.h"
#include "OnHitCharacterBase.h"

OnHitCharacterBase::OnHitCharacterBase(CharacterBase& owner) :
    OnHitBase(owner),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::STAGE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitStage(opponentCollider);
        });
    //onHitMap_.emplace(CollisionTags::TAG::AVILITY_BOX, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
    //    {
    //        return OnHitAvilityBox(opponentCollider);
    //    });
}


OnHitCharacterBase::~OnHitCharacterBase()
{
}

void OnHitCharacterBase::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
}

void OnHitCharacterBase::OnHitAvilityBox(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());

    const auto& opOwner = opponentCollider.lock()->GetOwner();

    //お互いのパラメータ
    ParameterActor& myParam = owner_.GetParameter();
    const ParameterActor& opParam = opOwner.GetParameter();

    //互いの重さ
    float myWeight = myParam.weight_;
    float opWeight = opParam.weight_;
    float weightTotal = myWeight + opWeight;
    float weightRatio = myWeight / weightTotal;

    //お互いの距離
    Vector2F diff = Vector2F::SubVector2F(opParam.pos_, myParam.pos_);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    //それぞれのめり込み量
	Vector2 hitSize = Vector2(myParam.hitSize_);
    float overlapX = static_cast<float>(hitSize.x / 2)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x);
    float overlapY = static_cast<float>(hitSize.y / 2)
        + static_cast<float>(collider->GetBoxHalfSize().y) - fabsf(diff.y);

    //移動量
    Vector2F moveAmount = myParam.moveAmount_;

    //ボックスの上に乗っているかを判断
    Vector2F pos = myParam.pos_;

    //ボックスの上に乗っていたら地面判定を付与
    if (overlapX > overlapY)
    {
        pos.y -= (overlapY + 0.01f) * signY;
        // 地面判定を設定
        myParam.isGround_ = true;

        //落下を防止するためにYの移動量をゼロにする
        moveAmount.y = 0;
        myParam.moveAmount_ = moveAmount;
        owner_.SetJumpPow(0.0f);
    }
    else
    {
        //ボックスを押し出す
        pos.x += overlapX * -weightRatio * signX;

    }

    //座標更新
    myParam.pos_ = pos;
}

void OnHitCharacterBase::OnHitAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 衝突者が無敵のときは無視
    if (owner_.IsInvincible() 
        || opponentCollider.lock()->GetPartnerTag() == CollisionTags::TAG::PLAYER_ATTACK_NORMAL
        || opponentCollider.lock()->GetPartnerTag() == CollisionTags::TAG::PLAYER_AVILITY_SHOT
        )
    {
        return;
    }

    // ノックバック処理
    KnockBack(opponentCollider, KNOCK_BACK_FORCE);

	// ダメージ処理
	Damage(opponentCollider);
}

bool OnHitCharacterBase::Damage(const std::weak_ptr<ColliderBase>& opponentCollider, int damage)
{
    // ダメージ量の指定がない場合
    if(damage < 0)
    {
        // 攻撃者の攻撃力をダメージ量とする
        damage = opponentCollider.lock()->GetOwner().GiveDamage();
	}
    // ダメージを与える
    owner_.Damage(damage, opponentCollider.lock()->GetHitPos());

	// ダメージを与えた結果、死亡しているか
	return owner_.GetState() == CharacterBase::STATE::DEAD;
}
void OnHitCharacterBase::KnockBack(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& knockBackForce)
{  
    // コライダー確認
    auto opponent = opponentCollider.lock();
    if (!opponent)
    {
        return;
    }
    
    // お互いのパラメータ情報を取得
    ParameterCharacter& myParameter = owner_.GetParameter();
    const ParameterActor& oppponentParameter = opponent->GetOwner().GetParameter();

    // 重力方向
    Vector2F gravityDir = myParameter.GetDown();

    // 重力に対する横方向
    Vector2F sideDir(-gravityDir.y, gravityDir.x);

    // 座標取得
    const Vector2F myPos = myParameter.pos_;
    const Vector2F opponentPos = oppponentParameter.pos_;

    // 相手から自分までの距離
    Vector2F toMe = Vector2F::SubVector2F(myPos, opponentPos);

    // 横方向距離
    const float sideDistance = Utility2D::Dot(toMe, sideDir);

    // コライダーサイズ
    const Vector2F mySize = myParameter.hitSize_.ToVector2F();
    Vector2  opponentSize = oppponentParameter.hitSize_;
    const Vector2F opponentSizeF = opponentSize.ToVector2F();

    // 横吹っ飛ばしが有効な最大距離
    const float maxDistance = (mySize.y * 0.5f) + (opponentSize.y * 0.5f);

    // 距離割合
    float ratio = fabsf(sideDistance) / maxDistance;
    ratio = std::clamp(ratio, 0.0f, 1.0f);

    // 横方向符号
    const float sideSign = sideDistance >= 0.0f ? 1.0f : -1.0f;

    // 横吹っ飛ばし
    Vector2F sideKnockBack = Vector2F::MulVector2FFloat(Vector2F::MulVector2FFloat(Vector2F::MulVector2FFloat(sideDir, knockBackForce.x), ratio), sideSign);

    // 重力逆方向吹っ飛ばし
    Vector2F verticalKnockBack =Vector2F::MulVector2FFloat(gravityDir, -knockBackForce.y);

    // 合成
	Vector2F finalPower = Vector2F::AddVector2F(sideKnockBack, verticalKnockBack);

    // セット
    myParameter.knockBackPower_ = finalPower;

    // 地面判定無効
    myParameter.isGround_ = false;

    // ジャンプを無効
    myParameter.jumpCount_--;
    myParameter.jumpPow_ = 0.0f;
}