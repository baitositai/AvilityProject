#include "../Manager/Game/StageManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../Object/Character/Player.h"
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
	if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_AVILITY))
	{
		//ボックスを置く
		PlaceBox();
	}
}

void ComponentAvilityBox::PlaceBox()
{
	//ボックスが３個までなら設置
	if (boxCnt_ < SET_BLAST_NUM)
	{
		//プレイヤーの座標からボックスの位置を決める
		const bool dir=owner_.GetParameter()->direction;
		const Vector2F pos = owner_.GetParameter()->pos;
		stageManager_.AddGimmick(pos,dir);

		//ボックスカウントを増加
		boxCnt_++;
	}
}
