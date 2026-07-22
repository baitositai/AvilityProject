#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Game/UiManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "../../Ui/Player/UiPlayerRespawnMessage.h"
#include "ComponentStatePlayerDead.h"

ComponentStatePlayerDead::ComponentStatePlayerDead(Player& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	inputManager_(InputManager::GetInstance())
{
	respownValue_ = -1;
}

ComponentStatePlayerDead::~ComponentStatePlayerDead()
{
}

void ComponentStatePlayerDead::Init()
{
	respownValue_ = 0;
	update_ = std::bind(&ComponentStatePlayerDead::UpdateStart, this);
}

void ComponentStatePlayerDead::Update()
{
	update_();
}

void ComponentStatePlayerDead::UpdateStart()
{
	soundManager_.PlaySe(SoundType::SE::DEAD);	
	update_ = std::bind(&ComponentStatePlayerDead::UpdateAnimation, this);
}

void ComponentStatePlayerDead::UpdateAnimation()
{
	// 死亡アニメーションが終了した場合
	if (owner_.GetAnimation().GetType() == Animation::TYPE::DEAD &&
		!owner_.GetAnimation().IsPlay())
	{
		// プレイヤーの場合は処理を無視
		if (owner_.GetType() == CharacterBase::TYPE::PLAYER)
		{
			// UI表示
			UiManager::GetInstance().Add(std::make_unique<UiPlayerRespawnMessage>(owner_));

			// 更新処理を変更
			update_ = std::bind(&ComponentStatePlayerDead::UpdateRespownAccept, this);
			return;
		}
		else
		{
			// 所有者を消す
			owner_.Delete();
		}
	}
}

void ComponentStatePlayerDead::UpdateRespownAccept()
{
	// リスポーン処理受付
	if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_RESPAWN, owner_.GetParameter().padNo_))
	{
		respownValue_++;
		if (respownValue_ > RESPAWN_CONDITION_INPUT_COUNT)
		{
			// 復活処理
			owner_.ChangeState(CharacterBase::STATE::SPAWN);
		}
	}
}