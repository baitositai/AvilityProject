#include <DxLib.h>
#include "../Manager/Common/ResourceManager.h"
#include "UiBase.h"

UiBase::UiBase() : 
	resourceManager_(ResourceManager::GetInstance())
{
	scale_ = 1.0f;
	angle_ = 0.0f;
	handle_ = -1;
	isActive_ = true;
	isDelete_ = false;
	pos_ = {};
}

UiBase::~UiBase()
{
}

void UiBase::Init()
{

}

void UiBase::Update()
{

}

void UiBase::Draw()
{
	if (isActive_)
	{
		DrawRotaGraph(
			pos_.x,
			pos_.y,
			scale_,
			angle_,
			handle_,
			true
		);
	}
}

void UiBase::Delete()
{
	isDelete_ = true;
}