#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Object/Character/Player.h"
#include "ComponentCameraRangeCheck.h"

ComponentCameraRangeCheck::ComponentCameraRangeCheck(Player& owner) :
	ComponentBase(owner),
	owner_(owner)
{
}

ComponentCameraRangeCheck::~ComponentCameraRangeCheck()
{
}

void ComponentCameraRangeCheck::Init()
{
}

void ComponentCameraRangeCheck::Update()
{
	// パラメータ取得
	ParameterActor& parameter = owner_.GetParameter();

	// カメラの左上座標を取得
	Vector2F cameraTopLeft = mainCamera.GetPos();
	cameraTopLeft = Vector2F::MulVector2FFloat(cameraTopLeft, -1.0f);

	// 画面の右下座標を計算
	Vector2F cameraBottomRight = Vector2F(
		cameraTopLeft.x + (float)Application::SCREEN_SIZE_X,
		cameraTopLeft.y + (float)Application::SCREEN_SIZE_Y
	);

	cameraBottomRight = Vector2F::MulVector2FFloat(cameraBottomRight, -1.0f);

	// セーフエリアとして広げるサイズ
	// 画面サイズに応じて調整してください
	const float SAFE_AREA_X = 0.0;
	const float SAFE_AREA_Y = 0.0f;

	// 生存範囲用にセーフエリアを広げる
	// 左上はさらに左上（Xマイナス、Yマイナス）へ広げる
	Vector2F top = Vector2F(cameraTopLeft.x - SAFE_AREA_X, cameraTopLeft.y - SAFE_AREA_Y);

	// 右下はさらに右下（Xプラス、Yプラス）へ広げる
	Vector2F bottom = Vector2F(cameraBottomRight.x + SAFE_AREA_X, cameraBottomRight.y + SAFE_AREA_Y);

	// アクターの各部位位置を取得
	Vector2F ownerPos = parameter.pos_;
	Vector2F ownerHitSize = parameter.hitSize_.ToVector2F();

	Vector2F actorTop = Vector2F::AddVector2F(ownerPos, Vector2F(0.0f, -ownerHitSize.y / 2.0f));
	Vector2F actorRight = Vector2F::AddVector2F(ownerPos, Vector2F(ownerHitSize.x / 2.0f, 0.0f));
	Vector2F actorLeft = Vector2F::AddVector2F(ownerPos, Vector2F(-ownerHitSize.x / 2.0f, 0.0f));
	Vector2F actorBottom = Vector2F::AddVector2F(ownerPos, Vector2F(0.0f, ownerHitSize.y / 2.0f));

	// 生存範囲内か調べる
	// 補正用に現在のアクター座標をローカル変数にコピー
	Vector2F correctedPos = ownerPos;
	float halfWidth = ownerHitSize.x / 2.0f;
	float halfHeight = ownerHitSize.y / 2.0f;

	// 左右のセーフエリア外に出ないようにする補正
	if (actorLeft.x < top.x)
	{
		correctedPos.x = top.x + halfWidth;
	}
	else if (actorRight.x > bottom.x)
	{
		correctedPos.x = bottom.x - halfWidth;
	}

	// 上のセーフエリア外に出ないようにする補正
	if (actorTop.y < top.y)
	{
		correctedPos.y = top.y + halfHeight;
	}

	// 左右や上に押し戻された座標を反映する
	if (correctedPos.x != ownerPos.x || correctedPos.y != ownerPos.y)
	{
		parameter.pos_ = correctedPos;
	}

	// 下のみ
	// アクターの頭頂部も含めて完全に下のセーフエリアを越えたら死亡とする
	if (actorTop.y > bottom.y)
	{
		// 死亡
		owner_.Dead();
	}
}
