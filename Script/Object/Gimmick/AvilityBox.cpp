#include "../Collider/ColliderBox.h"
#include "../OnHit/OnHitAvilityBox.h"
#include "AvilityBox.h"

AvilityBox::AvilityBox(const Parameter& parameter, const std::vector<std::string>& componentNameList):
	parameter_(parameter),
	GimmickBase(&parameter_,componentNameList)
{
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::AVILITY_BOX, parameter_.pos, parameter_.hitBoxSize, parameter_.angle);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitAvilityBox>(*this);

	// 基底クラスの初期化
	GimmickBase::Init();
}

AvilityBox::~AvilityBox()
{
}

void AvilityBox::Init(void)
{
	GimmickBase::Init();
}

void AvilityBox::Update(void)
{
	GimmickBase::Update();
	if (!collider_->IsHit()) { parameter_.moveAmount.x = 0.0f; }
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
