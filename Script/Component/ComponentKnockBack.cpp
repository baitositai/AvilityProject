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

    float deltTime = SceneManager::GetInstance().GetDeltaTime();
    owner_.AddMoveAmount(Vector2F::MulVector2F(knockBackPower, Vector2F(deltTime, deltTime)));

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
