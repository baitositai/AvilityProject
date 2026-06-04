#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentStateRespawn.h"

ComponentStateRespawn::ComponentStateRespawn(CharacterBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter()),
	sceneManager_(SceneManager::GetInstance())
{
	update_ = std::bind(&ComponentStateRespawn::UpdateReady, this);
}

ComponentStateRespawn::~ComponentStateRespawn()
{
}

void ComponentStateRespawn::Init()
{
	update_ = std::bind(&ComponentStateRespawn::UpdateReady, this);
}

void ComponentStateRespawn::Update()
{
	update_();
}

void ComponentStateRespawn::UpdateReady()
{
	// エフェクト生成

	// 更新処理変更
	update_ = std::bind(&ComponentStateRespawn::UpdateWait, this);
}

void ComponentStateRespawn::UpdateWait()
{
	waitTimer_ += sceneManager_.GetDeltaTime();
	if (waitTimer_ > RESPAWN_WAIT_TIME)
	{
		owner_.ChangeState(CharacterBase::STATE::ALIVE);
	}
}
