#include "../../Utility/UtilityLoad.h"
#include "../../Object/Gimmick/GimmickDoor.h"
#include "../../Object/Gimmick/GimmickTarget.h"
#include "../../Parameter/Gimmick/ParameterGimmickGroundRock.h"
#include "../../System/GimmickGenerator.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/SceneManager.h"
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
			// カメラ範囲内の場合
			auto& parameter = gimmick->GetParameter();
			bool isInScreen = mainCamera.IsInScreenBox(parameter.pos_, parameter.hitSize_, parameter.angle_);
			if (isInScreen)
			{
				gimmick->Update();
			}
			gimmick->SetIsActive(isInScreen);
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

void GimmickManager::CreateGroundRock(const CreateParameter& _parameter,const float _horizontalSpd)
{
	//GroundRock生成
	auto groundRock = gimmickGenerator_->Create(GimmickTypes::TYPE::GROUND_ROCK);

	//水平方向を設定
	auto& parameter = dynamic_cast<ParameterGimmickGroundRock&>(groundRock->GetParameter());
	parameter.pos_ = _parameter.pos;
	parameter.moveDir_ = _parameter.moveDir;

	//速度を設定できるようにする
	parameter.horizonSpd_ = _horizontalSpd;
	if (_parameter.hp > -1) { parameter.hp_ = _parameter.hp; }
	if (_parameter.attackPower > -1) { parameter.attackPower_ = _parameter.attackPower; }

	//初期化
	groundRock->Init();

	// 格納
	gimmickListMap_[GimmickTypes::TYPE::GROUND_ROCK].push_back(std::move(groundRock));
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