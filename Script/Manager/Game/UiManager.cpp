#include "../../Ui/UiBase.h"
#include "../../Ui/Game/UiMoney.h"
#include "../../Ui/Game/UiPlayerLeft.h"
#include "UiManager.h"

void UiManager::Init()
{
	if (uiList_.empty())
	{
		return;
	}
	for (const auto& ui : uiList_)
	{
		ui->Init();
	}
}
void UiManager::Update()
{
	if (uiList_.empty())
	{
		return;
	}
	for (const auto& ui : uiList_)
	{
		ui->Update();
	}
}
void UiManager::Draw()
{
	if (uiList_.empty())
	{
		return;
	}
	for (const auto& ui : uiList_)
	{
		ui->Draw();
	}
}
void UiManager::Add(std::unique_ptr<UiBase> ui)
{
	// 中身がある場合
	if (ui)
	{
		// 初期化
		ui->Init();

		// 追加
		uiList_.push_back(std::move(ui));
	}
}

void UiManager::CreateGameUi()
{
	Add(std::move(std::make_unique<UiMoney>()));
	Add(std::move(std::make_unique<UiPlayerLeft>()));
}

void UiManager::Sweep()
{
	// 終了したアイテムを並び変える
	auto it = std::remove_if(uiList_.begin(), uiList_.end(),
		[](const std::unique_ptr<UiBase>& item)
		{
			return item->IsDelete();
		});

	// 終了したコライダを削除する
	uiList_.erase(it, uiList_.end());
}

void UiManager::Clear()
{
	if (uiList_.empty())
	{
		return;
	}
	for (const auto& ui : uiList_)
	{
		ui->Delete();
	}
	uiList_.clear();
}

UiManager::UiManager()
{
}

UiManager::~UiManager()
{
}
