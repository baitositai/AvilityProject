#include "../../Object/Gimmick/GimmickShop.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SceneManager.h"
#include "UiShop.h"

UiShop::UiShop(const GimmickShop& owner) :
	owner_(owner)
{
	basePos_ = {};
	timer_ = 0.0f;
}

UiShop::~UiShop()
{
}

void UiShop::Init()
{
	Vector2F ownerPos = owner_.GetParameter().pos_;
	basePos_ = ownerPos.ToVector2() + Vector2(0, -80);
	pos_ = basePos_;
	handle_ = resourceManager_.GetHandle("uiShop");
	scale_ = 1.0f;
}

void UiShop::Draw()
{
    // タイマーを加算
    timer_ += SceneManager::GetInstance().GetDeltaTime();

    // 揺れのパラメータ設定
    const float AMPLITUDE = 10.0f; // 揺れ幅（上下に±10ピクセル）
    const float SPEED = 2.0f;      // 揺れる速度（数値が大きいほど速い）

    // サイン波を使ってY軸のオフセットを計算
    float offsetY = std::sin(timer_ * SPEED) * AMPLITUDE;

    // 計算したオフセットを反映
    pos_ = basePos_ + Vector2(0.0f, offsetY);
    Vector2F cameraPos = mainCamera.GetPos();
    Vector2 drawPos = pos_ + cameraPos.ToVector2();
	DrawRotaGraph(
		drawPos.x,
		drawPos.y,
		scale_,
		angle_,
		handle_,
		true
	);
}
