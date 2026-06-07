#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Object/Character/Player.h"
#include "ComponentStatePlayerSpawn.h"

ComponentStatePlayerSpawn::ComponentStatePlayerSpawn(Player& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter()),
	sceneManager_(SceneManager::GetInstance()),
	playerManager_(PlayerManager::GetInstance())
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
	// エフェクト生成

	// 更新処理変更
	update_ = std::bind(&ComponentStatePlayerSpawn::UpdateWait, this);

	// タイマー初期化
	waitTimer_ = 0.0f;
}

void ComponentStatePlayerSpawn::UpdateWait()
{
	waitTimer_ += sceneManager_.GetDeltaTime();
	if (waitTimer_ > RESPAWN_WAIT_TIME)
	{
		// 状態遷移
		owner_.ChangeState(CharacterBase::STATE::ALIVE);

		// 残機減らす
		playerManager_.AddPlayersLeft();

		// 残機数に応じてHP回復
		if (playerManager_.GetPlayerLeft() > 0)
		{
			// HPを最大回復
			parameter_.hp_ = parameter_.hpMax_;
		}
		else
		{
			// 最大HPの10%で回復
			parameter_.hp_ = parameter_.hpMax_ / 10;
		}

		// 画面中央に座標設定
		parameter_.pos_ = Vector2F::SubVector2F(Vector2F((float)Application::SCREEN_HALF_X, (float)Application::SCREEN_HALF_Y), mainCamera.GetPos());

		// コンポーネントを有効にする
		owner_.SetComponentActive("cameraRangeCheck", true);
		owner_.SetComponentActive("jump", true);

		// 活動状態を有効にする
		owner_.SetIsActive(true);

		// コライダーを有効にする
		owner_.SetColliderActive(true);
	}
}