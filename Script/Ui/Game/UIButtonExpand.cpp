#include "../../Manager/Common/ResourceManager.h"
#include "UIButtonExpand.h"

UIButtonExpand::UIButtonExpand()
{
}

UIButtonExpand::~UIButtonExpand()
{
}

void UIButtonExpand::Init()
{	// ‰Šú‰»ˆ—
	UiBase::Init();

	pos_ = Vector2(BUTTON_EXPAND_POS_X, BUTTON_EXPAND_POS_Y);
	scale_ = 1.0f;
	handle_= resourceManager_.GetHandle("buttonExpand");

	// ‰Šú‰»ˆ—
	InitNumber();
}
