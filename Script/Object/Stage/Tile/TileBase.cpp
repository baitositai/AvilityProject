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
	// タイルの仮描画
	int color = UtilityCommon::WHITE;	// 白色

	if (parameter_.type == TYPE::BLOCK)
	{
		color = UtilityCommon::BLUE;	// 青色
	}

	Vector2F cameraPos = mainCamera.GetPos();
	Vector2 rendererPos = Vector2::AddVector2(parameter_.position, cameraPos.ToVector2());

	DrawBox(
		rendererPos.x,
		rendererPos.y,
		rendererPos.x + SIZE_TILE,
		rendererPos.y + SIZE_TILE,
		color,
		true
	);

	DrawBox(
		rendererPos.x,
		rendererPos.y,
		rendererPos.x + SIZE_TILE,
		rendererPos.y + SIZE_TILE,
		UtilityCommon::RED,
		false
	);
}

void TileBase::DebugDraw()
{

}