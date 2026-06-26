#include "../../Utility/UtilityLoad.h"
#include "../../Object/Gimmick/GimmickDoor.h"
#include "../../Object/Gimmick/GimmickTarget.h"
#include "../../System/GimmickGenerator.h"
#include "GimmickManager.h"

void GimmickManager::Init()
{
	if (gimmickListMap_.empty()) return;

	for (auto& gimmickList : gimmickListMap_)
	{
		for (auto& gimmick : gimmickList.second)
		{
			gimmick->Init();
		}
	}
}

void GimmickManager::Update()
{
	if (gimmickListMap_.empty()) return;

	for (auto& gimmickList : gimmickListMap_)
	{
		for (auto& gimmick : gimmickList.second)
		{
			gimmick->Update();
		}
	}
}

void GimmickManager::Draw()
{
	if (gimmickListMap_.empty()) return;

	for (auto& gimmickList : gimmickListMap_)
	{
		for (auto& gimmick : gimmickList.second)
		{
			gimmick->Draw();
		}
	}
}

void GimmickManager::Sweep()
{
	if (gimmickListMap_.empty()) return;

	for (auto& gimmickList : gimmickListMap_)
	{
		auto it = std::remove_if(gimmickList.second.begin(), gimmickList.second.end(),
			[](const std::unique_ptr<GimmickBase>& gimmick)
			{
				if (gimmick == nullptr)
				{
					return true;
				}
				return gimmick->IsDelete();
			});
		gimmickList.second.erase(it, gimmickList.second.end());
	}
}

void GimmickManager::Clear()
{
	if (gimmickListMap_.empty())
	{
		return;
	}

	for (auto& gimmickList : gimmickListMap_)
	{
		for (auto& gimmick : gimmickList.second)
		{
			if (gimmick == nullptr)
			{
				continue;
			}
			gimmick->Delete();
			gimmick.reset();
		}
		gimmickList.second.clear();
	}
	gimmickListMap_.clear();
}

void GimmickManager::Create(const GimmickTypes::TYPE type, const Vector2F& pos, const Vector2F& moveDir)
{	
	// ¶¬
	auto gimmick = gimmickGenerator_->Create(type);

	// ‰Šúƒpƒ‰ƒ[ƒ^‚Ì’²®
	gimmick->GetParameter().pos_ = pos;
	gimmick->GetParameter().moveDir_ = moveDir;

	// ‰Šú‰»
	gimmick->Init();

	// Ši”[
	gimmickListMap_[type].push_back(std::move(gimmick));
}

void GimmickManager::CreateBossDoor(const Vector2F pos)
{
	// ƒhƒA¶¬
	auto door = gimmickGenerator_->Create(GimmickTypes::TYPE::DOOR);
	
	// À•W‚ÌÝ’è
	auto& parameter = door->GetParameter();
	parameter.pos_ = pos;
	parameter.pos_.y -= parameter.hitSize_.y / 2;

	// Ši”[
	gimmickListMap_[GimmickTypes::TYPE::DOOR].push_back(std::move(door));
}

void GimmickManager::AllDeleteTarget()
{
	for (auto& target : gimmickListMap_.at(GimmickTypes::TYPE::TARGET))
	{
		target->Delete();
	}
	gimmickListMap_.at(GimmickTypes::TYPE::TARGET).clear();
}

const bool GimmickManager::IsDestrolyAllTarget() const
{
	return gimmickListMap_.at(GimmickTypes::TYPE::TARGET).empty();
}

void GimmickManager::DebugDraw()
{
	if (gimmickListMap_.empty()) return;

	for (auto& gimmickList : gimmickListMap_)
	{
		for (auto& gimmick : gimmickList.second)
		{
			gimmick->DebugDraw();
		}
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