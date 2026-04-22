#include "ComponentAvilityBox.h"

ComponentAvilityBox::ComponentAvilityBox(Player& owner):
	ComponentAvilityBase(owner),
	boxCnt_(),
	coolCnt_()
{
}

ComponentAvilityBox::~ComponentAvilityBox()
{
}

void ComponentAvilityBox::Update()
{
	//プレイヤーがボックスを置く処理を書く
}
