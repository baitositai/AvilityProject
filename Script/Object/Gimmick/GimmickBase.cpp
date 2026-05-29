#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../Common/Animation.h"
#include "GimmickBase.h"

GimmickBase::GimmickBase(std::unique_ptr<ParameterGimmick> parameter) :
	ActorBase(std::move(parameter))
{
	gimmickType_ = TYPE::MAX;

	// パラメータ
	parameterGimmick_ = dynamic_cast<ParameterGimmick*>(GetParameterActorPtr());
	assert(parameterGimmick_ != nullptr);
}

GimmickBase::~GimmickBase()
{
}

void GimmickBase::Init(void)
{
	ActorBase::Init();
}

void GimmickBase::InitResource()
{
	// リソースに指定がない場合無視
	if (parameterGimmick_->resourceKey_ == "")
	{
		return;
	}

	// リソース取得
	parameterGimmick_->texture_ = resMng_.GetHandle(parameterGimmick_->resourceKey_);
}

void GimmickBase::Update(void)
{
	ActorBase::Update();
}

void GimmickBase::Draw(void)
{
	parameterGimmick_->drawPos_ = GetDrawPos();

	// 描画
	DrawRotaGraph(
		parameterGimmick_->drawPos_.x,
		parameterGimmick_->drawPos_.y,
		parameterGimmick_->scale_,
		parameterGimmick_->angle_,
		parameterGimmick_->texture_,
		parameterGimmick_->transparent_,
		parameterGimmick_->direction_
	);
}

void GimmickBase::DebugDraw(void)
{
	ActorBase::DebugDraw();
}