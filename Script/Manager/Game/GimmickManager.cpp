#include "../../Utility/UtilityLoad.h"
#include "../../Object/Gimmick/GimmickDoor.h"
#include "../../Object/Gimmick/GimmickTarget.h"
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
	auto parameter = GetGimmickParameter(GimmickBase::TYPE::DOOR);
	parameter->pos_ = pos;
	parameter->pos_.y -= parameter->hitSize_.y / 2;
	gimmickList_.push_back(std::make_unique<GimmickDoor>(std::move(parameter)));
}

void GimmickManager::DebugDraw()
{
	if (gimmickList_.empty()) return;

	for (auto& gimmick : gimmickList_)
	{
		gimmick->DebugDraw();
	}
}

std::unique_ptr<ParameterGimmick> GimmickManager::GetGimmickParameter(const GimmickBase::TYPE type) const
{
	return std::make_unique<ParameterGimmick>(*templateParameterMap_.at(type));
}

void GimmickManager::InitParameter()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("GimmickParameter");

	// ドア生成
	const auto jsonDoorParameter = jsonParameterMap.at("door").front();
	auto parameterDoor = std::make_unique<ParameterGimmick>();
	parameterDoor->LoadParameter(jsonDoorParameter);
	templateParameterMap_.emplace(GimmickBase::TYPE::DOOR, std::move(parameterDoor));

	// ターゲット生成
	const auto jsonTargetParameter = jsonParameterMap.at("target").front();
	auto parameterTarget = std::make_unique<ParameterGimmickTarget>();
	parameterTarget->LoadParameter(jsonTargetParameter);
	templateParameterMap_.emplace(GimmickBase::TYPE::TARGET, std::move(parameterTarget));
}

GimmickManager::GimmickManager()
{
	InitParameter();
}

GimmickManager::~GimmickManager()
{
}