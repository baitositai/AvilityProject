#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/StageManager.h"
#include "../../Object/Character/Player.h"
#include "ComponentAvilityBase.h"

ComponentAvilityBase::ComponentAvilityBase(Player& owner) :
	owner_(owner),
	stageManager_(StageManager::GetInstance()),
	sceneManager_(SceneManager::GetInstance()),
	soundManager_(SoundManager::GetInstance()),
	inputManager_(InputManager::GetInstance()),
	effectManager_(SpriteEffectManager::GetInstance()),
	collisionManager_(CollisionManager::GetInstance()),
	parameter_(owner.GetParameter()),
	ComponentBase(owner)
{
	type_ = AvilityTypes::TYPE::MAX;
}

ComponentAvilityBase::~ComponentAvilityBase()
{
}

void ComponentAvilityBase::Create()
{
	// バフを設定
	parameter_.SetAvilityBoost(type_);
}

void ComponentAvilityBase::Update()
{
}

void ComponentAvilityBase::Remove()
{
	// バフを外す
	parameter_.RemoveAvilityBoost(type_);
}
