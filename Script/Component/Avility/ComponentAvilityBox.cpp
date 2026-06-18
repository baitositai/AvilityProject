#include "../Manager/Game/StageManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../Object/Character/Player.h"
#include "ComponentAvilityBox.h"

ComponentAvilityBox::ComponentAvilityBox(Player& owner):
	ComponentAvilityBase(owner),
	boxCnt_(),
	coolCnt_()
{
	//type_ = AvilityTypes::TYPE::BOX;
}

ComponentAvilityBox::~ComponentAvilityBox()
{
}

void ComponentAvilityBox::Create()
{
	ComponentAvilityBase::Create();
	Init();
}

void ComponentAvilityBox::Init()
{
}

void ComponentAvilityBox::Update()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_SHOT, parameter_.padNo_))
	{
		//ボックスを置く
		PlaceBox();
	}
}

void ComponentAvilityBox::PlaceBox()
{
	const bool dir = parameter_.direction_;
	const Vector2F pos = parameter_.pos_;
	//ボックスが３個までなら設置
	if (boxCnt_ < SET_BLAST_NUM)
	{
		//プレイヤーの座標からボックスの位置を決める
		//stageManager_.AddGimmick(owner_, boxCnt_);

		//ボックスカウントを増加
		boxCnt_++;
	}
	else
	{
		////一番古いギミックを消去
		//stageManager_.DeleteGimmick();

		////新たにギミックを追加
		//stageManager_.AddGimmick(pos, dir);
	}
}
