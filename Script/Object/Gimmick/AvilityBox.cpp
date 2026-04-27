#include "../Manager/Common/SceneManager.h"
#include "../Collider/ColliderBox.h"
#include "../OnHit/OnHitAvilityBox.h"
#include "AvilityBox.h"

AvilityBox::AvilityBox(const Parameter& parameter,const Vector2F& _placePos,const std::vector<std::string>& componentNameList) :
	parameter_(parameter),
	GimmickBase(&parameter_,componentNameList)
{
	//種類の設定
	gimmickType_ = TYPE::AVILITY_BOX;

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::AVILITY_BOX, parameter_.pos, parameter_.hitBoxSize, parameter_.angle);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitAvilityBox>(*this);

}

AvilityBox::~AvilityBox()
{
}

void AvilityBox::Init(void)
{
	GimmickBase::Init();

	//座標をプレイヤーとローカル座標分離れている座標にする
	//parameter_.pos = Vector2F::AddVector2F(placePos_,parameter_.placePos);
	parameter_.pos = parameter_.placePos;
}

void AvilityBox::Update(void)
{
	if (collider_->IsHit())
	{
		parameter_.moveAmount = Vector2F();
	}

	GimmickBase::Update();

	//if (blastWaitCnt_ > 0.0f)
	//{
	//	blastWaitCnt_ -= scnMng_.GetDeltaTime();
	//}
	//else
	//{
	//	collider_->SetDelete();
	//	return;
	//}

}

void AvilityBox::Draw(void)
{
	GimmickBase::Draw();
}

void AvilityBox::DebugDraw(void)
{
	if (collider_ == nullptr) return;
	collider_->DebugDraw();
}
