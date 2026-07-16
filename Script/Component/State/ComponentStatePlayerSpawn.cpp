#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Object/Character/Player.h"
#include "ComponentStatePlayerSpawn.h"

ComponentStatePlayerSpawn::ComponentStatePlayerSpawn(Player& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter()),
	sceneManager_(SceneManager::GetInstance())
{
	waitTimer_ = 0.0f;
	update_ = std::bind(&ComponentStatePlayerSpawn::UpdateReady, this);
}

ComponentStatePlayerSpawn::~ComponentStatePlayerSpawn()
{
}

void ComponentStatePlayerSpawn::Init()
{
	update_ = std::bind(&ComponentStatePlayerSpawn::UpdateReady, this);
}

void ComponentStatePlayerSpawn::Update()
{
	update_();
}

void ComponentStatePlayerSpawn::UpdateReady()
{		
	// 画面中央に座標設定
	parameter_.pos_ = Vector2F::SubVector2F(Vector2F((float)Application::SCREEN_HALF_X, (float)Application::SCREEN_HALF_Y), mainCamera.GetPos());
	
	// エフェクト生成
	SpriteEffectManager::CreateParameter parameter;
	parameter.pos = parameter_.pos_;
	parameter.angle = parameter_.angle_;
	parameter.resourceKey = "effectRespawn";
	parameter.animationSpeed = 0.15f;
	SpriteEffectManager::GetInstance().Create(parameter);

	// 誕生処理
	owner_.Spawn();
	return;

	//// 更新処理変更
	//update_ = std::bind(&ComponentStatePlayerSpawn::UpdateWait, this);

	//// タイマー初期化
	//waitTimer_ = 0.0f;
}

void ComponentStatePlayerSpawn::UpdateWait()
{
	waitTimer_ += sceneManager_.GetDeltaTime();
	if (waitTimer_ > RESPAWN_WAIT_TIME)
	{		
		// 誕生処理
		owner_.Spawn();
	}
}