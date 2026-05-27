#pragma once
#include "ComponentBase.h"

class Player;

class ComponentCameraRangeCheck : public ComponentBase
{
public:

	ComponentCameraRangeCheck(Player& owner);
	~ComponentCameraRangeCheck() override;
	void Init() override;
	void Update() override;

private:

	Player& owner_;
};

