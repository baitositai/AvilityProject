#include "../Common/Animation.h"
#include "Train.h"

Train::Train(std::unique_ptr<ParameterActor> parameter) :
	ActorBase(std::move(parameter))
{
	parameterTrain_ = GetParameterActorPtr();
}

Train::~Train()
{
}

void Train::Draw()
{
	// アニメーション番号の指定
	parameterTrain_->drawIndex_ = animation_->GetAnimationIndex();

	// 基底クラスの処理
	ActorBase::Draw();
}