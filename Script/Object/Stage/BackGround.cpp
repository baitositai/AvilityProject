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

void BackGround::SetResource(const std::string& key)
{
	img_ = ResourceManager::GetInstance().GetHandle(key);
}