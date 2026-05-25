#include "../../../Manager/Common/Camera.h"
#include "../../../Manager/Common/SceneManager.h"
#include "../../../Utility/UtilityCommon.h"
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
	Vector2F cameraPos = mainCamera.GetPos();
	Vector2 rendererPos = Vector2::AddVector2(parameter_.position, cameraPos.ToVector2());
	DrawGraph(
		rendererPos.x,	
		rendererPos.y,
		parameter_.handle,
		true
	);
}

void TileBase::DebugDraw()
{	
	Vector2F cameraPos = mainCamera.GetPos();
	Vector2 rendererPos = Vector2::AddVector2(parameter_.position, cameraPos.ToVector2());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(
		rendererPos.x,
		rendererPos.y,
		rendererPos.x + SIZE_TILE,
		rendererPos.y + SIZE_TILE,
		UtilityCommon::BLACK,
		false
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}