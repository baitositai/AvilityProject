#include "../../Utility/UtilityLoad.h"
#include "../../Object/Gimmick/GimmickDoor.h"
#include "../../Object/Gimmick/GimmickTarget.h"
#include "../../System/GimmickGenerator.h"
#include "GimmickManager.h"

void GimmickManager::Init()
{
	if (gimmickList_.empty()) return;

	for (auto& gimmick : gimmickList_)
	{
		gimmick->Init();
	}
}

void GimmickManager::Update()
{
	if (gimmickList_.empty()) return;

	for (auto& gimmick : gimmickList_)
	{
		gimmick->Update();
	}
}

void GimmickManager::Draw()
{
	if (gimmickList_.empty()) return;

	for (auto& gimmick : gimmickList_)
	{
		gimmick->Draw();
	}
}

void GimmickManager::Sweep()
{
	if (gimmickList_.empty()) return;

	auto removeGim = std::remove_if(gimmickList_.begin(), gimmickList_.end(), [](std::unique_ptr<GimmickBase>& _gim)
		{
			return _gim->IsDelete();
		});
	gimmickList_.erase(removeGim, gimmickList_.end());
}

void GimmickManager::Clear()
{
	if (gimmickList_.empty()) return;

	for (auto& gimmick : gimmickList_)
	{
		gimmick->Delete();
	}
	gimmickList_.clear();
}

void GimmickManager::Add(std::unique_ptr<GimmickBase> gimmick)
{
	gimmickList_.push_back(std::move(gimmick));
}

void GimmickManager::SetBossDoor(const Vector2F pos)
{
	// ƒhƒA¶¬
	auto door = gimmickGenerator_->Create(GimmickTypes::TYPE::DOOR);
	
	// À•W‚ÌÝ’è
	auto& parameter = door->GetParameter();
	parameter.pos_ = pos;
	parameter.pos_.y -= parameter.hitSize_.y / 2;

	// Ši”[
	gimmickList_.push_back(std::move(door));
}

void GimmickManager::DebugDraw()
{
	if (gimmickList_.empty()) return;

	for (auto& gimmick : gimmickList_)
	{
		gimmick->DebugDraw();
	}
}

GimmickManager::GimmickManager()
{
	gimmickGenerator_ = std::make_unique<GimmickGenerator>();
	gimmickGenerator_->InitParameter();
}

GimmickManager::~GimmickManager()
{
}