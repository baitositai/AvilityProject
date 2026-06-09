#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/ResourceManager.h"
#include "BackGround.h"

BackGround::BackGround()
{
	img_ = -1;
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{

}

void BackGround::Update()
{

}

void BackGround::Draw()
{
	DrawExtendGraph(
		0,0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		img_,
		true
	);
}

void BackGround::SetType(const TYPE type)
{
}

void BackGround::SetResource(const std::string& key)
{
	img_ = ResourceManager::GetInstance().GetHandle(key);
}

void BackGround::UpdateFix()
{
}

void BackGround::UpdateScroll()
{
}

void BackGround::DrawFix()
{
	DrawExtendGraph(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		img_,
		true
	);
}

void BackGround::DrawScroll()
{
	DrawExtendGraph(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		img_,
		true
	);
}