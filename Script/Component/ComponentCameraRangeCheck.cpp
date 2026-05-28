#include <DxLib.h>
#include "../../Utility/UtilityCommon.h"
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
	constexpr float OFFSET_SIDE = 32;
	constexpr float OFFSET_BOTTOM = 128;

	// パラメータ取得
	ParameterActor& parameter = owner_.GetParameter();

	// セーフエリアの定義
	safeAreaTop_ = { -OFFSET_SIDE, 0 };
	safeAreaBottom_ = { Application::SCREEN_SIZE_X + OFFSET_SIDE, Application::SCREEN_SIZE_Y + OFFSET_BOTTOM };

	// カメラ座標を足す
	Vector2F cameraPos = mainCamera.GetPos();
	safeAreaTop_ = Vector2F::SubVector2F(safeAreaTop_, cameraPos);
	safeAreaBottom_ = Vector2F::SubVector2F(safeAreaBottom_, cameraPos);

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
	if (actorLeft.x < safeAreaTop_.x)
	{
		correctedPos.x = safeAreaTop_.x + halfWidth;
	}
	else if (actorRight.x > safeAreaBottom_.x)
	{
		correctedPos.x = safeAreaBottom_.x - halfWidth;
	}

	// 上のセーフエリア外に出ないようにする補正
	if (actorTop.y < safeAreaTop_.y)
	{
		correctedPos.y = safeAreaTop_.y + halfHeight;
	}

	// 左右や上に押し戻された座標を反映する
	if (correctedPos.x != ownerPos.x || correctedPos.y != ownerPos.y)
	{
		parameter.pos_ = correctedPos;
	}

	// 下のみ
	// アクターの頭頂部も含めて完全に下のセーフエリアを越えたら死亡とする
	if (actorTop.y > safeAreaBottom_.y)
	{
		// 死亡処理
		owner_.Dead();
	}
}

void ComponentCameraRangeCheck::DebugDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);

	// 描画用のスクリーン座標を計算（ワールド座標からカメラ座標を引く）
	// cameraTopLeft_自体がワールド座標なので、そこからカメラ位置を引きます
	Vector2F cameraPos = mainCamera.GetPos();
	float screenLeft = safeAreaTop_.x + cameraPos.x;
	float screenTop = safeAreaTop_.y + cameraPos.y;
	float screenRight = safeAreaBottom_.x + cameraPos.x;
	float screenBottom = safeAreaBottom_.y + cameraPos.y;

	DrawBox((int)screenLeft, (int)screenTop, (int)screenRight, (int)screenBottom, UtilityCommon::BLUE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 文字列表示用の座標もスクリーン座標に合わせるか、ワールド座標をそのまま出すか
	// ここでは描画された枠のスクリーン座標を表示するようにします
	DrawFormatString(0, Application::SCREEN_SIZE_Y - 40, UtilityCommon::RED, L"TOP %d,%d", (int)screenLeft, (int)screenTop);
	DrawFormatString(0, Application::SCREEN_SIZE_Y - 20, UtilityCommon::RED, L"BOT %d,%d", (int)screenRight, (int)screenBottom);
}