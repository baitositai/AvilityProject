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
    // 現在のノックバックパワーを取得
    Vector2F knockBackPower = owner_.GeKnockBackPower();

    // 0なら処理を抜ける
    if (knockBackPower.Length() < 0.1f)
    {
        return;
    }

    // 1フレーム分の移動量として現在のパワーを加算
    owner_.AddMoveAmount(knockBackPower);

    // 摩擦量で減衰（例：0.9倍にする）
    // 0.5fだと一瞬で止まってしまうため少し大きめの値がおすすめです
    knockBackPower = Vector2F::MulVector2F(knockBackPower, Vector2F(0.9f, 0.9f));

    // 速度が一定以下になったら完全に停止させる
    if (knockBackPower.Length() < 0.1f)
    {
        knockBackPower = { 0.0f, 0.0f };
    }

    // 減衰させた値を所有者に書き戻す
    // これにより、次回のUpdateでは減衰した値から始まります
    owner_.SetKnockBackPower(knockBackPower);
}
