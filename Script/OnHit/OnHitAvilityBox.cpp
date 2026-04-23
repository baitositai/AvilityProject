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
}

OnHitAvilityBox::~OnHitAvilityBox()
{
}

void OnHitAvilityBox::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    //プレイヤー
    const ActorBase& player = opponentCollider.lock()->GetOwner();
    //パラメーター
    const ActorBase::Parameter* playerParam = player.GetParameter();
    //移動量
    Vector2F moveAmount = playerParam->moveAmount;
    //プレイヤー座標
    Vector2F opponentPos = playerParam->pos;
    //相手のボックスコライダ
    auto playerCol = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());
    //-------------------------------------------------
    //ボックス
    //-------------------------------------------------
    //座標
    Vector2F ownerPos = owner_.GetParameter()->pos;
    //重さ
    float weight = owner_.GetWeight();
    //-------------------------------------------------
    //2間のベクトル
    Vector2F diff = Vector2F::SubVector2F(opponentPos, ownerPos);
    

    //箱に向かって動いていないときは処理しない
    if (UtilityCommon::GetSign(moveAmount.x) != UtilityCommon::GetSign(diff.x))
    {
        return;
    }
    //押し出し量
    float overlapX = owner_.GetHitBoxSize().x / 2 + playerCol->GetBoxHalfSize().x - std::fabsf(diff.x);

    //Y成分はなくす
    moveAmount.x = playerParam->moveAmount.x;
    moveAmount.y = 0.0f;
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