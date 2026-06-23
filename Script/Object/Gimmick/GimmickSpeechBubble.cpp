#include "../../Manager/Common/SceneManager.h"
#include "GimmickSpeechBubble.h"

GimmickSpeechBubble::GimmickSpeechBubble(std::unique_ptr<ParameterGimmickSpeechBubble> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterSpeechBubble_ = dynamic_cast<ParameterGimmickSpeechBubble*>(GetParameterGimmickPtr());
	assert(parameterSpeechBubble_ != nullptr);

	followPos_ = nullptr;
	timer_ = 0.0f;
}

GimmickSpeechBubble::~GimmickSpeechBubble()
{
}

void GimmickSpeechBubble::Init()
{
	InitResource();
	parameterSpeechBubble_->scale_ = 0.0f;
}

void GimmickSpeechBubble::Update()
{
	// 拡大処理
	if (parameterSpeechBubble_->scale_ < 1.0f) { parameterSpeechBubble_->scale_ += parameterSpeechBubble_->scaleUpSpeed_; }

	// 座標の追従
	parameterSpeechBubble_->pos_ = Vector2F::AddVector2F(*followPos_, parameterSpeechBubble_->localPos_.ToVector2F());

	// 時間処理
	timer_ += scnMng_.GetDeltaTime();
	if (parameterSpeechBubble_->displayTime_ < timer_)
	{
		Delete();
	}
}

void GimmickSpeechBubble::Set(const Vector2F* followPos, const std::string& resourceName, const float displayTime)
{
	followPos_ = followPos;
	if (displayTime >= 0.0f)
	{
		parameterSpeechBubble_->displayTime_ = displayTime;
	}
	parameterSpeechBubble_->resourceKey_ = resourceName;
	Init();
}