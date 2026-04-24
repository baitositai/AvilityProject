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
	if (boxCnt_ < SET_BLAST_NUM)
	{
		//プレイヤーがボックスを置く処理を書く
	}

}
