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
<<<<<<< HEAD
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
=======
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());
    if (!collider) return;

    // 当たったすべてのタイルインデックスを取得
    const auto& hitIndexes = collider->GetResult().hitIndexes;
    if (hitIndexes.empty()) return;
>>>>>>> main

    Vector2F pos = owner_.GetParameter()->pos;
   // Vector2F moveAmount = owner_.GetParameter()->moveAmount;
    Vector2 boxSize = owner_.GetHitBoxSize();
    Vector2 chipSize = collider->GetChipSize();

<<<<<<< HEAD

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
=======
    for (const auto& hitIndex : hitIndexes)
    {
        Vector2F moveAmount = owner_.GetParameter()->moveAmount;

        if (moveAmount.x == 0.0f && moveAmount.y == 0.0f)
        {
            break;
        }

        // 1. ボックス化（座標化）
        float tLeft = hitIndex.x * chipSize.x;
        float tRight = tLeft + chipSize.x;
        float tTop = hitIndex.y * chipSize.y;
        float tBottom = tTop + chipSize.y;

        // プレイヤーの四端
        float pLeft = pos.x - boxSize.x / 2.0f;
        float pRight = pos.x + boxSize.x / 2.0f;
        float pTop = pos.y - boxSize.y / 2.0f;
        float pBottom = pos.y + boxSize.y / 2.0f;

        // 2. どのくらいめり込んでいるか（ボックス同士の重なり）
        float overL = pRight - tLeft;
        float overR = tRight - pLeft;
        float overT = pBottom - tTop;
        float overB = tBottom - pTop;

        // 3. 最小のめり込み（一番浅い方向）を探して、その方向にだけ押し出す
        // こうすれば、地面のチップで「横押し出し」が暴走することはありません
        //float minOverlap = FLT_MAX;
        //int dir = -1; // 0:左, 1:右, 2:上, 3:下

        if (overL > 0 && overR > 0 && overT > 0 && overB > 0)
        {
            float minOverlap = 10000.0f;
            int dir = -1;

            // 【ここが重要】移動方向と矛盾しない押し出し方向だけを候補に入れる

            // 1. 右に移動中なら、左へ押し戻す判定を有効にする
            if (moveAmount.x > 0 && overL < minOverlap) { minOverlap = overL; dir = 0; }

            // 2. 左に移動中なら、右へ押し戻す判定を有効にする
            if (moveAmount.x < 0 && overR < minOverlap) { minOverlap = overR; dir = 1; }

            // 3. 下に移動（落下）中なら、上へ押し戻す（床）判定を有効にする
            if (moveAmount.y > 0 && overT < minOverlap) { minOverlap = overT; dir = 2; }

            // 4. 上に移動中なら、下へ押し戻す（天井）判定を有効にする
            if (moveAmount.y < 0 && overB < minOverlap) { minOverlap = overB; dir = 3; }

            // 決定した方向にのみ補正
            if (dir == 0) { pos.x -= (overL + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == 1) { pos.x += (overR + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == 2) { pos.y -= (overT + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }
            else if (dir == 3) { pos.y += (overB + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }

            owner_.SetPosition(pos);
        }
>>>>>>> main
    }

    // 衝突結果リセット
    collider->SetResult(ColliderArray::Result());
}