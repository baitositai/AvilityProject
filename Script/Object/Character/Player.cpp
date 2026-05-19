#include <DxLib.h>
#include "../../Component/Avility/ComponentAvilityBase.h"
#include "../../Component/Avility/AvilityTypes.h"
#include "../../OnHit/OnHitPlayer.h"
#include "../../Collider/ColliderBox.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "../Common/Animation.h"
#include "Player.h"

Player::Player(std::unique_ptr<ParameterPlayer> parameter, std::unique_ptr<Animation> animation) :
	CharacterBase(std::move(parameter), std::move(animation))
{	
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::PLAYER, parameterPlayer_->pos_, parameterPlayer_->hitSize_, parameterPlayer_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitPlayer>(*this);

	// プレイヤー用のパラメータ
	parameterPlayer_ = dynamic_cast<ParameterPlayer*>(GetParameterCharacterPtr());
	assert(parameterPlayer_ != nullptr);
}

Player::~Player()
{
}

void Player::Update()
{
	// 移動後の値を初期化
	parameterPlayer_->moveAmount_ = {};

	// 状態別処理
	UpdateComponentState();

	// アビリティ処理
	UpdateComponentAvility();

	// 基底クラスの処理
	ActorBase::Update();
}

void Player::DebugDraw()
{
	constexpr int MARGIN = 20;
	int posY = MARGIN;
	CharacterBase::DebugDraw();
	posY += MARGIN;
	DrawFormatString(0, posY, UtilityCommon::LIME, L"ジャンプ回数  :%d", parameterPlayer_->jumpCount_);
	posY += MARGIN;
	DrawFormatString(0, posY, UtilityCommon::LIME, L"プレイヤー位置:%2f,%2f", parameterPlayer_->pos_.x, parameterPlayer_->pos_.y);
	posY += MARGIN;
	componentMap_["debugCreateItemAvility"]->DebugDraw();

	for (auto& it : abilityComponents_)
	{
		posY += MARGIN;
		AvilityTypes::TYPE type = it.second->GetType();
		if (type == AvilityTypes::TYPE::MAX)
		{
			DrawFormatString(0, posY, UtilityCommon::LIME, L"none");
		}
		else
		{
			DrawFormatString(0, posY, UtilityCommon::LIME, L"%ls", AvilityTypes::AVILITY_NAME_MAP.at(type).c_str());
		}
	}
	
}

void Player::AttackReset()
{
	// 初期化
	componentStateMap_.at(STATE::ATTACK)->Init();
}

std::shared_ptr<ColliderBox> Player::CreateColliderClone()
{
	std::shared_ptr<ColliderBase> collider = collider_->Clone();
	std::shared_ptr<ColliderBox> colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider);
	return colliderBox;
}

void Player::SetAbilityComponent(std::unique_ptr<ComponentAvilityBase> component)
{
	if (!component) return;

	ABILITY_SLOT abilitySlot = component->GetAbilitySlot();
	if (abilitySlot == ABILITY_SLOT::MAX) return;

	// 既にスロットに存在する場合
	if (abilityComponents_[abilitySlot] != nullptr)
	{
		// 取り外し時の処理
		abilityComponents_[abilitySlot]->Remove();
	}

	// 新しいアビリティを設定
	abilityComponents_[abilitySlot] = std::move(component);
}

void Player::RemoveAbilityComponent(const ABILITY_SLOT abilitySlot)
{
	auto it = abilityComponents_.find(abilitySlot);
	if (it != abilityComponents_.end() && it->second != nullptr)
	{
		// 取り外し時の処理
		it->second->Remove();

		// 解放
		it->second.reset();
	}
}

void Player::UpdateComponentAvility()
{
	if (abilityComponents_.empty())
	{
		return;
	}

	for (auto& avility : abilityComponents_)
	{
		auto& avilityPtr = avility.second;

		// 中身が有効かチェック
		if (avilityPtr)
		{
			if (avilityPtr->IsActive())
			{
				// 更新処理
				avilityPtr->Update();
			}
		}
	}
}
