#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Collider/ColliderBox.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Effect/EffectTeleportEnter.h"
#include "../../Object/Effect/EffectTeleportExit.h"
#include "ComponentAvilityTeleport.h"

ComponentAvilityTeleport::ComponentAvilityTeleport(Player& owner) :
	ComponentAvilityBase(owner)
{
	moveTimer_ = 0.0f;
	changeTimer_ = 0.0f;
	abilitySlot_ = ABILITY_SLOT::SECOND;
	type_ = AvilityTypes::TYPE::TELEPORT;
	state_ = STATE::INPUT;
	update_ = std::bind(&ComponentAvilityTeleport::UpdateInput, this);
	stateChangeMap_.emplace(STATE::INPUT, std::bind(&ComponentAvilityTeleport::ChangeStateInput, this));
	stateChangeMap_.emplace(STATE::MOVE, std::bind(&ComponentAvilityTeleport::ChangeStateMove, this));
	stateChangeMap_.emplace(STATE::APPEAR, std::bind(&ComponentAvilityTeleport::ChangeStateAppear, this));
}

ComponentAvilityTeleport::~ComponentAvilityTeleport()
{
}

void ComponentAvilityTeleport::Update()
{
	update_();
}

void ComponentAvilityTeleport::Remove()
{

}

void ComponentAvilityTeleport::UpdateInput()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_TELEPORT))
	{
		ChangeState(STATE::MOVE);
	}
}

void ComponentAvilityTeleport::UpdateMove()
{
	// キーを押し続けていない・もしくは時間制限に達した場合
	moveTimer_ += sceneManager_.GetDeltaTime();
	if (!inputManager_.IsNew(InputManager::TYPE::AVILITY_TELEPORT) || moveTimer_ >= MOVE_TIME)
	{
		// 状態遷移
		ChangeState(STATE::APPEAR);
	}

	Vector2F moveAmount = {};

	// 上下左右移動処理
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT))
	{
		moveAmount.x += parameter_.moveSpeed_;
	}
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT))
	{
		moveAmount.x -= parameter_.moveSpeed_;
	}
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_UP))
	{
		moveAmount.y -= parameter_.moveSpeed_;
	}
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_DOWN))
	{
		moveAmount.y += parameter_.moveSpeed_;
	}

	// 移動量を更新
	parameter_.moveAmount_ = Vector2F::AddVector2F(moveAmount, parameter_.moveAmount_);

	// この処理の間無敵
	parameter_.invincibleTime_ = 1.0f;
}

void ComponentAvilityTeleport::UpdateAppear()
{
	// 一定時間未満の場合
	changeTimer_ += sceneManager_.GetDeltaTime();
	if (changeTimer_ < CHANGE_TIME)
	{
		// 無視
		return;
	}
	
	// 状態遷移
	ChangeState(STATE::INPUT);
}

void ComponentAvilityTeleport::ChangeState(const STATE state)
{
	state_ = state;
	stateChangeMap_[state]();
}

void ComponentAvilityTeleport::ChangeStateInput()
{
	update_ = std::bind(&ComponentAvilityTeleport::UpdateInput, this);

	// コンポーネントを有効にする
	owner_.SetComponentActive("gravity", true);
	owner_.SetStateComponentActive(Player::STATE::ATTACK, true);
	owner_.SetAbilityActive(ABILITY_SLOT::FIRST, true);

	// アニメーションリスタート
	owner_.GetAnimation().Restart();
}

void ComponentAvilityTeleport::ChangeStateMove()
{
	update_ = std::bind(&ComponentAvilityTeleport::UpdateMove, this);

	// 不要なコンポーネントを無効にする
	owner_.SetComponentActive("gravity", false);
	owner_.SetStateComponentActive(Player::STATE::ATTACK, false);
	owner_.SetAbilityActive(ABILITY_SLOT::FIRST, false);	
	
	// 不要なパラメータの値を初期化
	parameter_.jumpPow_ = 0.0f;
	parameter_.knockBackPower_ = {};	
	parameter_.isGround_ = false;

	// 描画を非表示
	owner_.SetIsDraw(false);

	// 移動制限時間を初期化
	moveTimer_ = 0.0f;
	
	// エフェクトを設定
	std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();
	parameter->pos_ = parameter_.pos_;
	parameter->angle_ = parameter_.angle_;
	parameter->hitSize_ = { 96, 96 };
	parameter->resourceKey_ = "teleportEnter";
	parameter->scale_ = 1.0f;
	parameter->divisionNum_ = { 9, 1 };
	parameter->transparent_ = true;
	parameter->moveSpeed_ = 3.0f;
	parameter->componentkeys_ = { "spriteAnimation" };
	parameter->animationDataMap_.emplace("effect", Animation::Data(0, 8, 0.2f));
	std::unique_ptr<EffectTeleportEnter> effect = std::make_unique<EffectTeleportEnter>(std::move(parameter));
	effectManager_.Add(std::move(effect));
}

void ComponentAvilityTeleport::ChangeStateAppear()
{
	update_ = std::bind(&ComponentAvilityTeleport::UpdateAppear, this);	

	// タイマー初期化
	changeTimer_ = 0.0f;

	// 少しだけ無敵
	parameter_.invincibleTime_ = FINISH_INVICIBLE_TIME;

	// 描画を非表示
	owner_.SetIsDraw(true);

	// エフェクトを設定
	std::unique_ptr<ParameterEffectTeleportExit> parameter = std::make_unique<ParameterEffectTeleportExit>();
	parameter->pos_ = parameter_.pos_;
	parameter->angle_ = parameter_.angle_;
	parameter->hitSize_ = { 96, 96 };
	parameter->resourceKey_ = "teleportExit";
	parameter->scale_ = 1.0f;
	parameter->divisionNum_ = { 11, 1 };
	parameter->transparent_ = true;
	parameter->moveSpeed_ = 3.0f;
	parameter->attackPower_ = parameter_.attackPower_;
	parameter->attackBoostRate_ = parameter_.attackBoostRate_;
	parameter->componentkeys_ = { "spriteAnimation" };
	parameter->animationDataMap_.emplace("effect", Animation::Data(0, 10, 0.2f));
	std::unique_ptr<EffectTeleportExit> effect = std::make_unique<EffectTeleportExit>(std::move(parameter));
	effectManager_.Add(std::move(effect));
}