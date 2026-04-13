#include "../../Utility/UtilityCommon.h"
#include "TileBase.h"

TileBase::TileBase(const Parameter& parameter) :
	parameter_(parameter)
{
}

TileBase::~TileBase()
{
}

void TileBase::Init()
{
}

void TileBase::Draw()
{
}

void TileBase::DebugDraw()
{
	int color = UtilityCommon::WHITE;	// îíêF

	if (parameter_.type == TYPE::BLOCK)
	{
		color = UtilityCommon::BLACK;	// çïêF
	}

	DrawBox(
		parameter_.position.x - SIZE_TILE / 2,
		parameter_.position.y - SIZE_TILE / 2,
		parameter_.position.y + SIZE_TILE / 2,
		parameter_.position.y + SIZE_TILE / 2,
		color,
		true
	);
}