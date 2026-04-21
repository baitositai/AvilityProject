#include "../Object/Character/Player.h"
#include "../Collider/ColliderArray.h"
#include "OnHitPlayer.h"

OnHitPlayer::OnHitPlayer(Player& owner) :
    OnHitBase(owner),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::STAGE , [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitStage(opponentCollider);
        });
}

OnHitPlayer::~OnHitPlayer()
{
}

void OnHitPlayer::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 必要な情報の取得
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());      // 配列用コライダーへ変換
    const Vector2 hitIndex = collider->GetResult().hitIndex;                                // 衝突結果からヒットしたインデックスを取得
    const Vector2F moveAmount = owner_.GetParameter()->moveAmount;                          // 移動量取得
    Vector2F pos = owner_.GetParameter()->pos;                                              // プレイヤー座標取得
    const Vector2 boxSize = owner_.GetHitBoxSize();                                         // プレイヤーの当たり判定サイズ
    Vector2 chipSize = collider->GetChipSize();                                             // チップサイズ
    
    // 当たったタイルの境界座標を計算
    float tileLeft = hitIndex.x * chipSize.x;
    float tileRight = tileLeft + chipSize.x;

    float tileTop = hitIndex.y * chipSize.y;
    float tileBottom = tileTop + chipSize.y;

    // 現在（移動後）のプレイヤーの矩形範囲
	float playerCenterX = pos.x;
    float playerLeft = pos.x - boxSize.x / 2.0f;
    float playerRight = pos.x + boxSize.x / 2.0f;
    float playerTop = pos.y - boxSize.y / 2.0f;
    float playerBottom = pos.y + boxSize.y / 2.0f;

    // めり込み量を計算
    float overlapX = 0.0f;
    float overlapY = 0.0f;


    //overlapは負の数にならない
    // 横側
	// 移動量の方向に応じてめり込み量を計算
    if (moveAmount.x > 0){ 
        overlapX = playerRight - tileLeft; }
    else if (moveAmount.x < 0){
        overlapX = playerLeft - tileRight; }
    // 縦側
    // 落下
    if (moveAmount.y > 0) { 
        overlapY = playerBottom - tileTop; }
	// 上昇
    else if (moveAmount.y < 0) { 
        overlapY = tileBottom - playerTop; }


    // 重なりが小さい方の軸を優先して補正する（重要：これによって横飛びを防ぐ）
    // Xのめり込みがYより小さければ「壁」として処理

    // 衝突している場合、かつXのめり込みがYのめり込みより小さい（またはYのめり込みがない）場合
    if (overlapX > 0 && (overlapX < overlapY || overlapY <= 0))
    {
		// 右の壁に当たっている場合
        if (moveAmount.x > 0)
        {
            pos.x -= overlapX;
        }
		// 左の壁に当たっている場合
        else if (moveAmount.x < 0)
        {
			pos.x += overlapX;
            /*float tile = (hitIndex.x + 1) * chipSize.x;
            pos.x = tile + (boxSize.x / 2.0f) + 0.01f;*/
        }
        // X軸の移動量のみリセット
        owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y));
    }
    
    // Yのめり込みがXより小さければ「床・天井」として処理
    if (overlapY > 0)
    {
		// 下に当たっている場合　(床はこれ)
        if (moveAmount.y > 0)
        {
			pos.y -= overlapY;
            //pos.y = dtileTop - boxSize.y / 2.0f;
            // isOnGround = true; // 必要ならここで設定
        }
		// 上に当たっている場合
        else if (moveAmount.y < 0)
        {
            pos.y += overlapY;

            //pos.y = tileBottom + boxSize.y / 2.0f;
        }
        // Y軸の移動量のみリセット
        owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f));
    }

    // 座標の設定
    owner_.SetPosition(pos);

    // 移動量を初期化
    owner_.SetMoveAmount(Vector2F(0.0f, 0.0f));

    // 判定結果を初期化
    collider->SetResult(ColliderArray::Result());
}
