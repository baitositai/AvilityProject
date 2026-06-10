#include <DxLib.h>
#include "../../Common/Vector2.h"
#include "../../Application.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "BackGround.h"

BackGround::BackGround()
{
	scrollSpeed_ = 0.0f;
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
	update_();
}

void BackGround::Draw()
{
	draw_();
}

void BackGround::SetType(const TYPE type)
{
	if (type == TYPE::SCROLL)
	{
		update_ = std::bind(&BackGround::UpdateScroll, this);
		draw_ = std::bind(&BackGround::DrawScroll, this);

		// ç¿ïWê›íË
		scrollPos_[0].x = 0.0f;
		scrollPos_[1].x = (float)Application::SCREEN_SIZE_X - OFFSET;
	}
	else
	{
		update_ = std::bind(&BackGround::UpdateFix, this);
		draw_ = std::bind(&BackGround::DrawFix, this);
	}
}

void BackGround::SetResource(const std::string& key)
{
	img_ = ResourceManager::GetInstance().GetHandle(key);
}

void BackGround::SetScrollSpeed(const float scrollSpeed)
{
	scrollSpeed_ = scrollSpeed;
}

void BackGround::UpdateFix()
{
}

void BackGround::UpdateScroll()
{
	for (auto& pos : scrollPos_)
	{
		pos.x += scrollSpeed_;
		if (pos.x < (float)-Application::SCREEN_SIZE_X - OFFSET)
		{
			pos.x = (float)Application::SCREEN_SIZE_X - OFFSET;
		}
	}
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
	static constexpr int OFFSET = 3;
	Vector2F offsetF = mainCamera.GetOffset();
	Vector2 offset = offsetF.ToVector2();
	for (auto& posF : scrollPos_)
	{
		Vector2 pos = Vector2::AddVector2(posF.ToVector2(), offset);
		DrawExtendGraph(
			pos.x - OFFSET, pos.y - OFFSET,
			pos.x + Application::SCREEN_SIZE_X + OFFSET,
			pos.y + Application::SCREEN_SIZE_Y + OFFSET,
			img_,
			true
		);
	}
}