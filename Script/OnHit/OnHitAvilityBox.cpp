#include "../Utility/UtilityCommon.h"
#include "../Object/Gimmick/AvilityBox.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "./OnHitAvilityBox.h"
#include "OnHitItem.h"

OnHitAvilityBox::OnHitAvilityBox(AvilityBox& owner):
	OnHitBase(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayer(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitEnemy(opponentCollider);
		});
    onHitMap_.emplace(CollisionTags::TAG::STAGE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitStage(opponentCollider);
        });
    onHitMap_.emplace(CollisionTags::TAG::AVILITY_BOX, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitBox(opponentCollider);
        });
}

OnHitAvilityBox::~OnHitAvilityBox()
{
}

void OnHitAvilityBox::HitWall(void)
{
    if (owner_.GetIsHitWall()) { moveAmount_.x = 0.0f; }
}

void OnHitAvilityBox::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());

    const auto& opOwner = opponentCollider.lock()->GetOwner();    

    //お互いのパラメータ
    ParameterActor& myParam = owner_.GetParameter();
    const ParameterActor& opParam = opOwner.GetParameter();

    //プレイヤーが動いてなければ飛ばす
    if(Vector2F::IsSameVector2F(opParam.moveAmount_,Vector2F()))return;
    
    //互いの重さ
    float myWeight = myParam.weight_;
    float opWeight = opParam.weight_;
    float weightDiff = myWeight + opWeight;
    float weightRatio = myWeight / weightDiff;

    //お互いの距離
    Vector2F diff = Vector2F::SubVector2F(opParam.pos_, myParam.pos_);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    //それぞれのめり込み量
    float overlapX = static_cast<float>(myParam.hitSize_.x / 2)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x);
    float overlapY = static_cast<float>(myParam.hitSize_.y / 2)
        + static_cast<float>(collider->GetBoxHalfSize().y) - fabsf(diff.y);

    Vector2F moveAmount = Vector2F();
    moveAmount.x = moveAmount_.x;
    moveAmount.y = 0.0f;

    float myUpPosY = myParam.pos_.y - myParam.hitSize_.y / 2;
    float opDownPosY = opParam.pos_.y + collider->GetBoxHalfSize().y;

    //当たっている対象が自分より上にいたら処理を飛ばす
    Vector2F pos = myParam.pos_;
    Vector2F prevPos = myParam.pos_;

    //ボックスの押し出し
    if (overlapX < overlapY)
    {
        bool dir = opParam.direction_;

        //方向をセット
        myParam.direction_ = dir;

        //プレイヤーに押し出されているフラグ
        owner_.SetPlayerPush();

        //プッシュ
        pushDir_ = dir;

        pos.x += overlapX * -weightRatio * signX;
        //moveAmount = Vector2F::SubVector2F(pos, prevPos);
        moveAmount_ = Vector2F::SubVector2F(pos, prevPos);
        HitWall();
        if (!Vector2F::IsSameVector2F(moveAmount_, Vector2F()))
        {
            int i = 0;
        }
    }
    else
    {
        return;
    }

}
void OnHitAvilityBox::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
}

void OnHitAvilityBox::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
}

void OnHitAvilityBox::OnHitBox(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    ParameterAvilityBox& myParam = owner_.GetParameter();

    int boxNum = myParam.boxNum_;

    auto collider = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());

    const ActorBase& opOwnerBase = opponentCollider.lock()->GetOwner();

    const AvilityBox* opOwner =
        dynamic_cast<const AvilityBox*>(&opOwnerBase);

    bool isPlayerPush = owner_.GetIsPlayerPush();
    bool opPlayerPush = opOwner->GetIsPlayerPush();

    //お互いのパラメータ
    const ParameterActor& opParam = opOwner->GetParameter();

    //お互いの距離
    Vector2F diff = Vector2F::SubVector2F(opParam.pos_, myParam.pos_);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    //それぞれのめり込み量
    float overlapX = static_cast<float>(myParam.hitSize_.x / 2)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x);
    float overlapY = static_cast<float>(myParam.hitSize_.y / 2)
        + static_cast<float>(collider->GetBoxHalfSize().y) - fabsf(diff.y);

    Vector2F moveAmount = myParam.moveAmount_;
    Vector2F opMoveAmount = opParam.moveAmount_;

    //互いの重さ
    float myWeight = myParam.weight_;
    float opWeight = opParam.weight_;
    float weightTotal = myWeight + opWeight;
    float weightRatio = opWeight / weightTotal;

    Vector2F pos= myParam.pos_;
    Vector2F prevPos = myParam.pos_;
    bool opDir = opParam.direction_;

    //ボックスの押し出し
    if (overlapX < overlapY)
    {
        //プレイヤー押し出し中のボックスより先に
        //プレイヤーが押し出してないボックスのほうが先に当たった場合
        if (isPlayerPush && !opPlayerPush)
        {
            pos.x += (overlapX + 0.01f) * signX;
        }
        else
        {
            pos.x += -(overlapX + 0.01f) * signX;
        }
        moveAmount_ = opParam.moveAmount_;
        if (opOwner->GetIsHitWall())
        {
            moveAmount_.x = 0.0f;
        }
        HitWall();
    }
    else
    {
        pos.y += (overlapY)* -signY;
    }

    // 座標格納
    myParam.direction_ = opDir;
    myParam.pos_ = pos;
}