#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Common/Animation.h"
#include "ComponentStateDead.h"

ComponentStateDead::ComponentStateDead(CharacterBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	inputManager_(InputManager::GetInstance())
{
	respownValue_ = -1;
}

ComponentStateDead::~ComponentStateDead()
{
}

void ComponentStateDead::Init()
{
	respownValue_ = 0;
	update_ = std::bind(&ComponentStateDead::UpdateAnimation, this);
}

void ComponentStateDead::Update()
{
	update_();
}

void ComponentStateDead::UpdateAnimation()
{
	// 死亡アニメーションが終了した場合
	if (owner_.GetAnimation().GetType() == Animation::TYPE::DEAD &&
		!owner_.GetAnimation().IsPlay())
	{
		// プレイヤーの場合は処理を無視
		if (owner_.GetType() == CharacterBase::TYPE::PLAYER)
		{
			update_ = std::bind(&ComponentStateDead::UpdateRespownAccept, this);
			return;
		}
		else
		{	
			// 所有者を消す
			owner_.Delete();
		}
	}
}

void ComponentStateDead::UpdateRespownAccept()
{
	// リスポーン処理受付
	if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_RESPAWN))
	{
		respownValue_++;
		if (respownValue_ > RESPAWN_CONDITION_INPUT_COUNT)
		{
			// 復活処理
			owner_.ChangeState(CharacterBase::STATE::SPAWN);
		}
	}
}