#include "../../Manager/Common/SceneManager.h"
#include "../Object/Character/CharacterBase.h"
#include "ComponentKnockBack.h"

ComponentKnockBack::ComponentKnockBack(CharacterBase& owner) :
	ComponentBase(&owner),
	owner_(owner)
{
}

ComponentKnockBack::~ComponentKnockBack()
{
}

void ComponentKnockBack::Update()
{
    //// 現在のノックバックパワーを取得
    Vector2F knockBackPower = owner_.GeKnockBackPower();

    // 0なら処理を抜ける
    if (knockBackPower.Length() < 0.1f)
    {
        return;
    }

    //// 1フレーム分の移動量として現在のパワーを加算
    //owner_.AddMoveAmount(knockBackPower);

    //// 摩擦量で減衰（例：0.9倍にする）
    //// 0.5fだと一瞬で止まってしまうため少し大きめの値がおすすめです
    //knockBackPower = Vector2F::MulVector2F(knockBackPower, Vector2F(0.7f, 0.7f));

    //// 速度が一定以下になったら完全に停止させる
    //if (knockBackPower.Length() < 0.1f)
    //{
    //    knockBackPower = { 0.0f, 0.0f };
    //}

    //// 減衰させた値を所有者に書き戻す
    //// これにより、次回のUpdateでは減衰した値から始まります
    //owner_.SetKnockBackPower(knockBackPower);


    //float remainingDistance = owner_.GetKnockBackDistance();

    //// 残り距離がなければ何もしない
    //if (remainingDistance <= 0.0f)
    //{
    //    return;
    //}

    //// 1フレームで進む距離を計算する
    //// 一定速度で飛ばす場合は定数、減速させる場合は残り距離に応じた値にする
    //float moveDist = remainingDistance * 0.2f;

    //// 最低速度を下回らないように、あるいは行き過ぎないように調整
    //if (moveDist < 1.0f) moveDist = 1.0f;
    //if (moveDist > remainingDistance) moveDist = remainingDistance;

    //// 移動量を計算して所有者に加算
    //Vector2F moveStep = Vector2F::MulVector2F(Vector2F(1.0f, -0.2f), Vector2F(moveDist, moveDist));
    //owner_.AddMoveAmount(moveStep);

    //// 動いた分を残り距離から引く
    //remainingDistance -= moveDist;

    //// 完全に移動しきったらリセット
    //if (remainingDistance <= 0.0f)
    //{
    //    remainingDistance = 0.0f;
    //    //direction_ = { 0.0f, 0.0f };
    //}

    //owner_.SetKnockBackDistance(remainingDistance);

    float deltTime = SceneManager::GetInstance().GetDeltaTime();
    owner_.AddMoveAmount(Vector2F::MulVector2F(knockBackPower, Vector2F(deltTime, deltTime)));
    //owner_.AddMoveAmount(knockBackPower);

    // ノックバックの減衰
    if (knockBackPower.x != 0.0f) 
    {
        int sign = knockBackPower.x / fabsf(knockBackPower.x);

        knockBackPower.x += (-1.0f * sign) * 1200.0f * deltTime;

        if (knockBackPower.x / fabsf(knockBackPower.x) != sign) 
        {
            knockBackPower.x = 0.0f;
        }
    }
    if (knockBackPower.y != 0.0f)
    {
        int sign = knockBackPower.y / fabsf(knockBackPower.y);

        knockBackPower.y += (-1.0f * sign) * 1200.0f * deltTime;

        if (knockBackPower.y / fabsf(knockBackPower.y) != sign) 
        {
            knockBackPower.y = 0.0f;
        }
    }

    owner_.SetKnockBackPower(knockBackPower);
}
