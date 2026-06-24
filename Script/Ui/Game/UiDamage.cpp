#include <DxLib.h>
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Utility/UtilityCommon.h"
#include "UiDamage.h"

UiDamage::UiDamage(const int damage, const Vector2& pos, const IntVector3& color):
	sceneManager_(SceneManager::GetInstance())
{	
	drawCount_ = damage;
	pos_ = pos;
	color_ = color;
	damagePos_ = pos_.ToVector2F();
	alpha_ = 0.0f;
	timer_ = 0.0f;
}

UiDamage::~UiDamage()
{
}

void UiDamage::Init()
{
	// 数字の初期化
	InitNumber();
	numberSize_ = { 24,24 };
	numberScale_ = 0.19f;

	// 削除時間
	timer_ = DELETE_TIME;

	// α初期値
	alpha_ = UtilityCommon::ALPHA_MAX;
}

void UiDamage::Update()
{
	// α値の更新
	alpha_ -= ALPHA_SPEED;
	if (alpha_ < 0.0f)
	{
		// 削除処理
		Delete();
		return;
	}

	// 上方向に少し移動
	damagePos_.y -= MOVE_SPEED;
}

void UiDamage::Draw()
{
	// カメラ位置を加算
	Vector2F cameraPos = mainCamera.GetPos();
	numberStartDrawPos_ = Vector2::AddVector2(damagePos_.ToVector2(), cameraPos.ToVector2());

	// 描画
	SetDrawAddColor(color_.x, color_.y, color_.z);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);	
	DrawNumber();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawAddColor(0, 0, 0);
}