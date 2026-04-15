#include "../../Object/ActorBase.h"
#include "ComponentMove.h"

ComponentMove::ComponentMove(ActorBase& owner) :
	ComponentBase(&owner)
{
}

ComponentMove::~ComponentMove()
{
}

void ComponentMove::Update()
{
	// 移動量の取得
	Vector2F moveAmount = owner_->GetParameter()->moveAmount;

	// 移動量が0の場合は更新しない
	if (moveAmount.x == 0.0f && moveAmount.y == 0.0f)
	{
		return;
	}

	// 現在の位置を取得
	Vector2F pos = owner_->GetParameter()->pos;
	
	// 移動量を加算して位置を更新
	pos = Vector2F::AddVector2F(pos, moveAmount);

	// 更新した位置を設定
	owner_->SetPosition(pos);
}
