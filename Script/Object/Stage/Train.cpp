#include "Train.h"

Train::Train(std::unique_ptr<ParameterActor> parameter) :
	ActorBase(std::move(parameter))
{
	parameterTrain_ = GetParameterActorPtr();
}

Train::~Train()
{
}