#pragma once
#include "../ActorBase.h"

class Train : public ActorBase
{
public:

	Train(std::unique_ptr<ParameterActor> parameter);
	~Train() override;

private:

	ParameterActor* parameterTrain_;
};