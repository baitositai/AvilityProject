#include "../../Ui/UiBase.h"
#include "../../Ui/Game/UiMoney.h"
#include "../../Ui/Game/UiPlayerLeft.h"
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

void UiManager::CreateGameUi()
{
	Add(std::move(std::make_unique<UiMoney>()));
	Add(std::move(std::make_unique<UiPlayerLeft>()));
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

UiManager::UiManager()
{
}

UiManager::~UiManager()
{
}
