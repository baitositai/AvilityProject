#include "../Utility/UtilityCommon.h"
#include "../Object/Gimmick/AvilityBox.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "./OnHitAvilityBox.h"

OnHitAvilityBox::OnHitAvilityBox(AvilityBox& owner):
	OnHitBase(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayer(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::ENEMY, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
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

void OnHitAvilityBox::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());

    const auto& opOwner = opponentCollider.lock()->GetOwner();

    //お互いのパラメータ
    const ActorBase::Parameter* myParam = owner_.GetParameter();
    const ActorBase::Parameter* opParam = opOwner.GetParameter();

    //互いの重さ
    float myWeight = myParam->weight;
    float opWeight = opParam->weight;
    float weightDiff = myWeight + opWeight;
    float weightRatio = myWeight / weightDiff;

    //お互いの距離
    Vector2F diff = Vector2F::SubVector2F(opParam->pos, myParam->pos);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    //それぞれのめり込み量
    float overlapX = static_cast<float>(owner_.GetHitBoxSize().x/2)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x);
    float overlapY = static_cast<float>(owner_.GetHitBoxSize().y/2)
        + static_cast<float>(collider->GetBoxHalfSize().y) - fabsf(diff.y);

    Vector2F moveAmount = Vector2F();
    moveAmount.x = myParam->moveAmount.x;
    moveAmount.y = 0.0f;

    float myUpPosY = myParam->pos.y - owner_.GetHitBoxSize().y / 2;
    float opDownPosY = opParam->pos.y + collider->GetBoxHalfSize().y;

    //当たっている対象が自分より上にいたら処理を飛ばす
    Vector2F pos = myParam->pos;
    Vector2F prevPos = myParam->pos;;

    //ボックスの押し出し
    if (overlapX < overlapY)
    {
        pos.x += overlapX * -weightRatio * signX;
        moveAmount = Vector2F::SubVector2F(pos, prevPos);
    }
    else
    {
        return;
    }

    //ステータスをセット
    //owner_.SetPosition(pos);
    owner_.SetMoveAmount(moveAmount);

}
void OnHitAvilityBox::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{

}
void OnHitAvilityBox::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());
    if (!collider) return;              // コライダーが空の場合終了

    // 当たったすべてのタイルインデックスを取得
    const auto& indexes = collider->GetResult().indexes;
    if (indexes.empty()) return;       // インデックスリストが空の場合終了

    Vector2F pos = owner_.GetParameter()->pos;          // 座標取得
    Vector2 boxSize = owner_.GetHitBoxSize();           // ボックスサイズ          
    Vector2 chipSize = collider->GetChipSize();         // チップサイズ

    for (const Vector2& index : indexes)
    {
        // 移動量取得
        Vector2F moveAmount = owner_.GetParameter()->moveAmount;

        // 移動量が0の場合
        if (moveAmount.x == 0.0f && moveAmount.y == 0.0f)
        {
            // 終了
            break;
        }

        // タイルの四隅
        float tLeft = index.x * chipSize.x;
        float tRight = tLeft + chipSize.x;
        float tTop = index.y * chipSize.y;
        float tBottom = tTop + chipSize.y;

        // プレイヤーの四端
        float pLeft = pos.x - boxSize.x / 2.0f;
        float pRight = pos.x + boxSize.x / 2.0f;
        float pTop = pos.y - boxSize.y / 2.0f;
        float pBottom = pos.y + boxSize.y / 2.0f;

        // どのくらいめり込み具合
        float overL = pRight - tLeft;
        float overR = tRight - pLeft;
        float overT = pBottom - tTop;
        float overB = tBottom - pTop;

        if (overL > 0 && overR > 0 && overT > 0 && overB > 0)
        {
            float minOverlap = 10000.0f;
            ActorBase::DIR dir = ActorBase::DIR::MAX;

            // 右に移動中の場合
            if (moveAmount.x > 0 && overL < minOverlap)
            {
                // 左へ押し戻す判定を有効にする
                minOverlap = overL;
                dir = ActorBase::DIR::LEFT;
            }
            // 左に移動中の場合
            if (moveAmount.x < 0 && overR < minOverlap && pBottom >= tBottom)
            {
                // 右へ押し戻す判定を有効にする
                minOverlap = overR;
                dir = ActorBase::DIR::RIGHT;
            }

            // 落下中の場合　
            if (moveAmount.y > 0 && overT < minOverlap)
            {
                // 上へ押し戻す判定を有効にする
                minOverlap = overT;
                dir = ActorBase::DIR::UP;
            }
            // 上に移動中の場合　
            if (moveAmount.y < 0 && overB < minOverlap)
            {
                // 下へ押し戻す判定を有効にする
                minOverlap = overB;
                dir = ActorBase::DIR::DOWN;
            }

            // 決定した方向にのみ補正
            Vector2F MoveAmount = Vector2F(0.0f, 0.0f);
            if (dir == ActorBase::DIR::LEFT) { pos.x -= (overL + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == ActorBase::DIR::RIGHT) { pos.x += (overR + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == ActorBase::DIR::UP) { pos.y -= (overT + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }
            else if (dir == ActorBase::DIR::DOWN) { pos.y += (overB + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }

            // 座標格納
            owner_.SetPosition(pos);
        }
    }
}

void OnHitAvilityBox::OnHitBox(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    int i = 0;
}
