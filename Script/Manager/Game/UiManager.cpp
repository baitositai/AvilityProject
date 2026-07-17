#include "../../Ui/UiBase.h"
#include "../../Ui/Game/UiMoney.h"
#include "../../Ui/Game/UiPlayerLeft.h"
#include "../../Ui/Game/UiButtonExpand.h"
#include "../../Ui/Player/UiPlayerGetItemMessage.h"
#include "UiManager.h"

void UiManager::Init()
{
	if (uiMap_.empty())
	{
		return;
	}
	for (const auto& uiList : uiMap_)
	{
		for (const auto& ui : uiList.second)
		{
			ui->Init();
		}
	}
}
void UiManager::Update()
{
	if (uiMap_.empty())
	{
		return;
	}
	for (const auto& uiList : uiMap_)
	{
		for (const auto& ui : uiList.second)
		{
			ui->Update();
		}
	}
}
void UiManager::Draw(const LAYER layer)
{	
	if (uiMap_[layer].empty())
	{
		return;
	}
	for (const auto& ui : uiMap_[layer])
	{
		
		ui->Draw();
	}
}

void UiManager::Add(std::unique_ptr<UiBase> ui, const LAYER layer)
{	
	// ’†g‚ª‚ ‚éê‡
	if (ui)
	{
		// ‰Šú‰»
		ui->Init();

		// ’Ç‰Á
		uiMap_[layer].push_back(std::move(ui));
	}
}

void UiManager::AddGetItemMessageUI(std::unique_ptr<UiPlayerGetItemMessage> ui, const LAYER layer = LAYER::UI)
{
	for (const auto& ui : uiMap_)
	{
		auto& uiArray = ui.second;
		auto it = std::find_if(uiArray.begin(), uiArray.end(), [&](const auto& p)
			{
				auto message = dynamic_cast<UiPlayerGetItemMessage*>(p.get());
				return message != nullptr;
			});

		////“¯‚¶UI‚ªŒ©‚Â‚©‚Á‚½‚çã‘‚«‚·‚é
		//if (it != uiArray.end())
		//{
		//	*it = std::move(ui);
		//}
	}
}

void UiManager::CreateGameUi()
{
	Add(std::move(std::make_unique<UiMoney>()));
	Add(std::move(std::make_unique<UiPlayerLeft>()));
	Add(std::move(std::make_unique<UIButtonExpand>()));
}

void UiManager::Sweep()
{
	for (auto& uiList : uiMap_)
	{
		auto it = std::remove_if(uiList.second.begin(), uiList.second.end(),
			[](const std::unique_ptr<UiBase>& ui)
			{
				if (ui == nullptr)
				{
					return true;
				}
				return ui->IsDelete();
			});
		uiList.second.erase(it, uiList.second.end());
	}
}

void UiManager::Clear()
{
	if (uiMap_.empty())
	{
		return;
	}
	for (const auto& uiList : uiMap_)
	{
		for (const auto& ui : uiList.second)
		{
			ui->Delete();
		}
	}
	uiMap_.clear();
}

void UiManager::SetAllIsActive(const bool isActive, const LAYER layer)
{
	if (uiMap_.empty())
	{
		return;
	}
	for (auto& ui : uiMap_.at(layer))
	{
		ui->SetIsActive(isActive);
	}
}

UiManager::UiManager()
{
}

UiManager::~UiManager()
{
}
