#include <DxLib.h>
#include "../../Utility/UtilityCommon.h"
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Object/Character/Player.h"
#include "ComponentCameraRangeCheck.h"

ComponentCameraRangeCheck::ComponentCameraRangeCheck(Player& owner) :
	ComponentBase(owner),
	owner_(owner),
	collisionManager_(CollisionManager::GetInstance())
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

	ParameterActor& parameter = owner_.GetParameter();

	safeAreaTop_ =
	{
		-OFFSET_SIDE, 0
	};
	safeAreaBottom_ =
	{
		Application::SCREEN_SIZE_X + OFFSET_SIDE, Application::SCREEN_SIZE_Y + OFFSET_BOTTOM
	};

	Vector2F cameraPos = mainCamera.GetPos();
	safeAreaTop_ = Vector2F::SubVector2F(safeAreaTop_, cameraPos);
	safeAreaBottom_ = Vector2F::SubVector2F(safeAreaBottom_, cameraPos);

	Vector2F ownerPos = parameter.pos_;
	Vector2F ownerHitSize = parameter.hitSize_.ToVector2F();

	Vector2F actorTop = Vector2F::AddVector2F(ownerPos, Vector2F(0.0f, -ownerHitSize.y / 2.0f));
	Vector2F actorRight = Vector2F::AddVector2F(ownerPos, Vector2F(ownerHitSize.x / 2.0f, 0.0f));
	Vector2F actorLeft = Vector2F::AddVector2F(ownerPos, Vector2F(-ownerHitSize.x / 2.0f, 0.0f));

	Vector2F correctedPos = ownerPos;
	float halfWidth = ownerHitSize.x / 2.0f;
	float halfHeight = ownerHitSize.y / 2.0f;

	bool isPushedX = false;
	bool isPushedY = false;
	float pushDirectionX = 0.0f;
	float pushDirectionY = 0.0f;

	if (actorLeft.x < safeAreaTop_.x)
	{
		correctedPos.x = safeAreaTop_.x + halfWidth;
		isPushedX = true;
		pushDirectionX = 1.0f;
	}
	else if (actorRight.x > safeAreaBottom_.x)
	{
		correctedPos.x = safeAreaBottom_.x - halfWidth;
		isPushedX = true;
		pushDirectionX = -1.0f;
	}

	if (actorTop.y < safeAreaTop_.y)
	{
		correctedPos.y = safeAreaTop_.y + halfHeight;
		isPushedY = true;
		pushDirectionY = 1.0f;
	}

	if (isPushedX)
	{
		CollisionManager::CollisionCheckParam paramX;
		paramX.pos = Vector2(static_cast<int>(correctedPos.x), static_cast<int>(correctedPos.y));
		paramX.size = Vector2(static_cast<int>(ownerHitSize.x), static_cast<int>(ownerHitSize.y));
		paramX.isXAxis = true;
		paramX.stepMove = pushDirectionX;

		auto resultX = collisionManager_.CheckStageCollision(paramX);
		if (resultX.isHit)
		{
			owner_.Dead();
			return;
		}
	}

	if (isPushedY)
	{
		CollisionManager::CollisionCheckParam paramY;
		paramY.pos = Vector2(static_cast<int>(correctedPos.x), static_cast<int>(correctedPos.y));
		paramY.size = Vector2(static_cast<int>(ownerHitSize.x), static_cast<int>(ownerHitSize.y));
		paramY.isXAxis = false;
		paramY.stepMove = pushDirectionY;

		auto resultY = collisionManager_.CheckStageCollision(paramY);
		if (resultY.isHit)
		{
			owner_.Dead();
			return;
		}
	}

	if (isPushedX || isPushedY)
	{
		parameter.pos_ = correctedPos;
	}

	if (actorTop.y > safeAreaBottom_.y)
	{
		owner_.Dead();
		return;
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