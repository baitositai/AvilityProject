#include "../../Manager/Common/SceneManager.h"
#include "../Object/Character/CharacterBase.h"
#include "ComponentKnockBack.h"

ComponentKnockBack::ComponentKnockBack(CharacterBase& owner) :
	ComponentBase(owner),
    parameter_(owner.GetParameter())
{
}

ComponentKnockBack::~ComponentKnockBack()
{
}

void ComponentKnockBack::Update()
{
    //// 現在のノックバックパワーを取得
    Vector2F knockBackPower = parameter_.knockBackPower_;

    // 0なら処理を抜ける
    if (knockBackPower.Length() < 0.1f)
    {
        return;
    }

    float deltTime = SceneManager::GetInstance().GetDeltaTime();
    parameter_.knockBackPower_ = Vector2F::AddVector2F(parameter_.knockBackPower_, Vector2F::MulVector2F(knockBackPower, Vector2F(deltTime, deltTime)));

    // ノックバックの減衰
    if (knockBackPower.x != 0.0f) 
    {
        int sign = knockBackPower.x / fabsf(knockBackPower.x);

        knockBackPower.x += (-1.0f * sign) * KNOCK_BACK_DECELERATION * deltTime;

        if (knockBackPower.x / fabsf(knockBackPower.x) != sign) 
        {
            knockBackPower.x = 0.0f;
        }
    }
    if (knockBackPower.y != 0.0f)
    {
        int sign = knockBackPower.y / fabsf(knockBackPower.y);

        knockBackPower.y += (-1.0f * sign) * KNOCK_BACK_DECELERATION * deltTime;

        if (knockBackPower.y / fabsf(knockBackPower.y) != sign) 
        {
            knockBackPower.y = 0.0f;
        }
    }

    parameter_.knockBackPower_ = knockBackPower;
}
