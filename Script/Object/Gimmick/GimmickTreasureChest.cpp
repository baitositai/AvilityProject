#include "../../Collider/ColliderBox.h"
#include "../../OnHit/OnHitTreasureChest.h"
#include "../Common/Animation.h"
#include "GimmickTreasureChest.h"

GimmickTreasureChest::GimmickTreasureChest(std::unique_ptr<ParameterGimmickTreasureChest> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterTreasureChest_ = dynamic_cast<ParameterGimmickTreasureChest*>(GetParameterGimmickPtr());
	assert(parameterTreasureChest_ != nullptr);
}

GimmickTreasureChest::~GimmickTreasureChest()
{
}

void GimmickTreasureChest::Init()
{
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::TREASURE_CHEST, parameterTreasureChest_->pos_, parameterTreasureChest_->hitSize_, parameterTreasureChest_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitTreasureChest>(*this);

	// 基底クラスの初期化処理
	GimmickBase::Init();

	// 再生停止
	animation_->Play(Animation::TYPE::WALK, false);
	animation_->Stop();

	// 位置を調整
	parameterTreasureChest_->pos_.y -= parameterTreasureChest_->hitSize_.y / 2;
}

void GimmickTreasureChest::Update()
{
	// 基底クラスの処理
	ActorBase::Update();

	if (collider_->IsActive()) return;

	if (!animation_->IsPlay())
	{
		Delete();
	}
}

void GimmickTreasureChest::Draw()
{
	ActorBase::Draw();
}

void GimmickTreasureChest::InitResource()
{
	ActorBase::InitResource();
}

void GimmickTreasureChest::InitDraw()
{
	ActorBase::InitDraw();
}