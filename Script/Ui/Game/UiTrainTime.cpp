#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiTrainTime.h"

UiTrainTime::UiTrainTime() :
	sceneManager_(SceneManager::GetInstance())
{
	alpha_ = 0.0f;
	scale_ = 0.0f;
	timer_ = 0.0f;
	update_ = std::bind(&UiTrainTime::UpdateScale, this);
}

UiTrainTime::~UiTrainTime()
{
}

void UiTrainTime::Init()
{
	handle_ = resourceManager_.GetHandle("uiTrainTime");
	pos_ = Vector2(Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y);
	alpha_ = UtilityCommon::ALPHA_MAX;
}

void UiTrainTime::Update()
{
	update_();
}

void UiTrainTime::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	UiBase::Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void UiTrainTime::UpdateScale()
{
	timer_ += sceneManager_.GetDeltaTime();
	scale_ = UtilityCommon::EaseInQuad(timer_, SCALE_UP_TIME, 0.0f, SCALE_GOAL);

	constexpr float OFFSET = 0.001f;
	if (SCALE_GOAL - OFFSET <= scale_)
	{
		scale_ = SCALE_GOAL;
		timer_ = WAIT_TIME;
		update_ = std::bind(&UiTrainTime::UpdateWait, this);
	}
}

void UiTrainTime::UpdateWait()
{
	timer_ -= sceneManager_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		update_ = std::bind(&UiTrainTime::UpdateExit, this);
	}
}

void UiTrainTime::UpdateExit()
{
	alpha_ -= ALPHA_SUB_SPEED;
	if (alpha_ <= 0.0f)
	{
		Delete();
	}
}
