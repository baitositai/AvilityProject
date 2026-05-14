#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentInvincible.h"

ComponentInvincible::ComponentInvincible(CharacterBase& owner) :
	owner_(owner),
	sceneManager_(SceneManager::GetInstance()),
	ComponentBase(&owner)
{
	// 待機状態に遷移
	updateFunc_ = std::bind(&ComponentInvincible::Wait, this);
}

ComponentInvincible::~ComponentInvincible()
{
}

void ComponentInvincible::Update()
{
	updateFunc_();
}

void ComponentInvincible::Wait()
{
	if(owner_.IsInvincible())
	{
		// 無敵状態に遷移
		updateFunc_ = std::bind(&ComponentInvincible::SubInvincibleTime, this);

		// 所有者のコライダーの判定を無効化する
		owner_.SetColliderActive(false);
	}
}

void ComponentInvincible::SubInvincibleTime()
{
	// 無敵時間を減らす
	owner_.AddInvincibleTime(-sceneManager_.GetDeltaTime());

	// まだ無敵中の場合
	if (owner_.IsInvincible())
	{
		// 終了
		return;
	}

	// 待機状態に遷移
	updateFunc_ = std::bind(&ComponentInvincible::Wait, this);
	
	// 所有者のコライダーの判定を有効化する
	owner_.SetColliderActive(true);
}
