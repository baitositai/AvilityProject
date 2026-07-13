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

void GimmickManager::Create(const CreateParameter& parameter)
{	
	// 生成
	auto gimmick = gimmickGenerator_->Create(parameter.type);

	// 初期パラメータの調整
	auto& parameterGimmick = gimmick->GetParameter();
	parameterGimmick.pos_ = parameter.pos;
	parameterGimmick.moveDir_ = parameter.moveDir;
	if (parameter.hp > -1) { parameterGimmick.hp_ = parameter.hp; }
	if (parameter.attackPower > -1) { parameterGimmick.attackPower_ = parameter.attackPower; }

	// 初期化
	gimmick->Init();

	// 格納
	gimmickListMap_[parameter.type].push_back(std::move(gimmick));
}

void GimmickManager::CreateBossDoor(const Vector2F& pos)
{
	// ドア生成
	auto door = gimmickGenerator_->Create(GimmickTypes::TYPE::DOOR);
	
	// 座標の設定
	auto& parameter = door->GetParameter();
	parameter.pos_ = pos;
	parameter.pos_.y -= parameter.hitSize_.y / 2;

	// 格納
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

const Vector2F GimmickManager::GetShopPos() const
{
	// キーを探す
	const auto it = gimmickListMap_.find(GimmickTypes::TYPE::SHOP);

	// マップに存在しない場合
	if (it == gimmickListMap_.end())
	{
		return Vector2F();
	}

	// 座標を返す
	return gimmickListMap_.at(GimmickTypes::TYPE::SHOP).front()->GetParameter().pos_;
}

GimmickManager::GimmickManager()
{
	gimmickGenerator_ = std::make_unique<GimmickGenerator>();
	gimmickGenerator_->InitParameter();
}

GimmickManager::~GimmickManager()
{
}