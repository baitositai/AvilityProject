#include "ParameterGimmickSpeechBubble.h"

ParameterGimmickSpeechBubble::ParameterGimmickSpeechBubble() :
	scaleUpSpeed_(0.0f),
	displayTime_(0.0f)
{
}

ParameterGimmickSpeechBubble::~ParameterGimmickSpeechBubble()
{
}

void ParameterGimmickSpeechBubble::LoadParameter(const Json& parameter)
{
    // ì«Ç›çûÇ›èàóù
    ParameterActor::LoadParameter(parameter);
    scaleUpSpeed_ = parameter.value("scaleUpSpeed", 0.0f);
    displayTime_ = parameter.value("displayTime", 0.0f);
}
