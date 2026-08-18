#include "UiWarning.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/SceneManager.h"

UiWarning::UiWarning(const EnemyBase& owner) : 
	owner_(owner)
{
	deleteTimer_ = 0.0f;
}

UiWarning::~UiWarning()
{
}

void UiWarning::Init()
{
	handle_ = resourceManager_.GetHandle("uiWarning");
	scale_ = 0.5f;
	deleteTimer_ = owner_.GetParameter().attackDelayTime_;
}

void UiWarning::Update()
{
	deleteTimer_ -= SceneManager::GetInstance().GetDeltaTime();
	if (deleteTimer_ <= 0.0f)
	{
		Delete();
	}
}

void UiWarning::Draw()
{
	if (isDelete_)
	{
		return;
	}

	// 警告表示の点滅周期（秒単位）
	constexpr float FLASH_INTERVAL = 0.1f;
	
	// プレイヤーの活動状況に応じて活動状態を変更
	isActive_ = owner_.IsActive();
	pos_ = owner_.GetParameter().drawPos_;
	pos_.y -= owner_.GetParameter().hitSize_.y / 2 + 32;

	// 残り時間から経過時間を算出して点滅を判定
	int flashIndex = static_cast<int>(deleteTimer_ / FLASH_INTERVAL);
	if (flashIndex % 2 == 0)
	{
		return;
	}

	// 描画処理
	UiBase::Draw();
}