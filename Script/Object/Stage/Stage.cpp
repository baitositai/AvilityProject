#include "../Application.h"
#include "../Utility/UtilityLoad.h"
#include "Tile/TileBase.h"
#include "Stage.h"

Stage::Stage()
{
	// タイルの読み込み
	UtilityLoad::LoadCSVData(Application::PATH_CSV + PATH_STAGE);
}

Stage::~Stage()
{
}

void Stage::Init()
{
	// タイルの初期化
	
}

void Stage::Update()
{

}

void Stage::Draw()
{

}

void Stage::DebugDraw()
{

}
