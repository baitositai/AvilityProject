#include <DxLib.h>
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Component/Avility/ComponentAvilityBase.h"
#include "../../Component/Avility/AvilityTypes.h"
#include "../../OnHit/OnHitPlayer.h"
#include "../../Collider/ColliderBox.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "../Common/Animation.h"
#include "Player.h"

Player::Player(std::unique_ptr<ParameterPlayer> parameter) :
	CharacterBase(std::move(parameter))
{		
	// プレイヤー用のパラメータ
	parameterPlayer_ = dynamic_cast<ParameterPlayer*>(GetParameterCharacterPtr());
	assert(parameterPlayer_ != nullptr);

	// 種類定義
	type_ = TYPE::PLAYER;

	// 攻撃用のタグの設定
	parameterPlayer_->attackCollisionTag_ = CollisionTags::TAG::PLAYER_ATTACK_NORMAL;
	
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::PLAYER, parameterPlayer_->pos_, parameterPlayer_->hitSize_, parameterPlayer_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitPlayer>(*this);

	// 変数初期化
	selectAvilityTime_ = 0.0f;
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

	GameLeave();
}

void Player::Delete()
{
	for (auto& component : avilityComponents_)
	{
		component->Remove();
	}
	avilityComponents_.clear();

	CharacterBase::Delete();
}

void Player::DebugDraw()
{
	// カメラ範囲のデバッグ描画
	//componentMap_["cameraRangeCheck"]->DebugDraw();

	// 基底クラスのデバッグ描画
	CharacterBase::DebugDraw();

	// 選ぶやつのデバッグ描画
	componentMap_["debugCreateItemAvility"]->DebugDraw();

	// メッセージ
	std::vector<std::wstring> mess(AVILITY_MAX, L"none");

	// 種類取得
	int index = 0;
	for (auto& avility : avilityComponents_)
	{
		mess[index] = UtilityCommon::GetWStringFromString(AvilityTypes::AVILITY_NAME_MAP.at(avility->GetType()).c_str());
		index++;
	}

	// 描画
	DrawFormatString(
		parameterPlayer_->drawPos_.x - parameterPlayer_->hitSize_.x / 2,
		parameterPlayer_->drawPos_.y - parameterPlayer_->hitSize_.y / 2 - 80,
		UtilityCommon::RED, 
		L"1.%ls  2.%ls  3.%ls",
		mess[0].c_str(),
		mess[1].c_str(),
		mess[2].c_str());

	if (spareAvilityComponent_)
	{
		DrawFormatString(
			parameterPlayer_->drawPos_.x - parameterPlayer_->hitSize_.x / 2,
			parameterPlayer_->drawPos_.y - parameterPlayer_->hitSize_.y / 2 - 100,
			UtilityCommon::RED,
			L"交代するアビリティを選んでください");
	}
}

void Player::Dead()
{
	// 基底クラスの死亡処理
	CharacterBase::Dead();

	// 全てのアビリティを無効にする
	SetAllAvilityComponentActive(false);

	// カメラ範囲チェックのコンポーネントを無効にする
	SetComponentActive("cameraRangeCheck", false);

	// 残機を減らす
	PlayerManager::GetInstance().AddPlayersLeft();

	// ヒットストップ
	scnMng_.SetHitStop(0.5f);

	// カメラシェイク
	mainCamera.SetCameraShake(0.3f, 8.0f);
}

void Player::AttackAfter()
{
	CharacterBase::AttackAfter();

	SetAllAvilityComponentActive(true);
}

std::shared_ptr<ColliderBox> Player::CreateColliderClone()
{
	std::shared_ptr<ColliderBase> collider = collider_->Clone();
	std::shared_ptr<ColliderBox> colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider);
	return colliderBox;
}

void Player::SetAvilityComponent(std::unique_ptr<ComponentAvilityBase> component)
{
	// 中身が空の場合
	if (!component)
	{
		// 終了
		return;
	}

	// 既に所持しているか探索
	auto it = std::find_if(avilityComponents_.begin(), avilityComponents_.end(), [&component](const auto& avility)
		{
			return avility->GetType() == component->GetType();
		});

	// ある場合
	if (it != avilityComponents_.end())
	{
		// 終了
		return;
	}

	// 最大数所持してた場合
	if (static_cast<int>(avilityComponents_.size()) == AVILITY_MAX)
	{
		// スペアで所持
		spareAvilityComponent_ = std::move(component);

		// 操作が被るため一時的にアビリティ重力を無効にする
		SetAvilityActive(AvilityTypes::TYPE::GRAVITY, false);

		// 選択時間の設定
		selectAvilityTime_ = AVILITY_SELECT_TIME;

		// 終了
		return;
	}

	// 格納
	component->Init();
	avilityComponents_.push_back(std::move(component));
}

void Player::SetAvilityActive(const AvilityTypes::TYPE avilityType, const bool isActive)
{
	auto it = std::find_if(avilityComponents_.begin(), avilityComponents_.end(), [avilityType](const auto& avility)
		{
			return avility->GetType() == avilityType;
		});

	if (it != avilityComponents_.end())
	{
		(*it)->SetActive(isActive);
	}
}

void Player::SetAllAvilityComponentActive(const bool isActive)
{
	for (auto& avility : avilityComponents_)
	{
		avility->SetActive(isActive);
	}
}

void Player::RemoveAvilityComponent(const AvilityTypes::TYPE avilityType)
{
	auto it = std::remove_if(avilityComponents_.begin(), avilityComponents_.end(), [avilityType](const auto& avility)
		{
			if (avility->GetType() == avilityType)
			{
				avility->Remove();
				return true;
			}
			return false;
		});

	avilityComponents_.erase(it, avilityComponents_.end());
}

void Player::ResetAvilityComponent(const AvilityTypes::TYPE avilityType)
{
	auto it = std::find_if(avilityComponents_.begin(), avilityComponents_.end(), [avilityType](const auto& avility)
		{
			return avility->GetType() == avilityType;
		});

	if (it != avilityComponents_.end())
	{
		(*it)->Init();
	}
}

void Player::UpdateComponentAvility()
{
	if (avilityComponents_.empty())
	{
		return;
	}

	// アビリティの選択処理
	SelectAvility();

	// アビリティの処理
	for (auto& avility : avilityComponents_)
	{
		// 中身が有効かチェック
		if (avility)
		{
			if (avility->IsActive())
			{
				// 更新処理
				avility->Update();
			}
		}
	}
}

void Player::SelectAvility()
{
	// 予備の中身がある場合
	if (spareAvilityComponent_)
	{
		// 時間を減らす
		selectAvilityTime_ -= scnMng_.GetDeltaTime();

		// 選択処理
		int index = -1;
		InputManager& input = InputManager::GetInstance();
		if (input.IsTrgDown(InputManager::TYPE::SELECT_AVILITY_FIRST)) { index = 0; }
		else if (input.IsTrgDown(InputManager::TYPE::SELECT_AVILITY_SECOND)) { index = 1; }
		else if(input.IsTrgDown(InputManager::TYPE::SELECT_AVILITY_THIRD)) { index = 2; }

		// 選択した場合
		if (index > -1)
		{
			avilityComponents_[index]->Remove();
			spareAvilityComponent_->Init();
			avilityComponents_[index] = std::move(spareAvilityComponent_);
			selectAvilityTime_ = 0.0f;
		}

		// 時間に達した場合
		if (selectAvilityTime_ <= 0.0f)
		{
			spareAvilityComponent_ = nullptr;
			SetAvilityActive(AvilityTypes::TYPE::GRAVITY, true);
		}
	}
}

void Player::GameLeave()
{
	// 1Pのみ処理無効
	if (parameterPlayer_->padNo_ == Input::JOYPAD_NO::PAD1) { return; }

	// 一定以上長押しで退出
	InputManager& input = InputManager::GetInstance();
	if (input.IsNew(InputManager::TYPE::PLAYER_GAME_LEAVE, parameterPlayer_->padNo_))
	{
		if (LEAVE_INPUT_TIME > leaveInputTime_)
		{
			leaveInputTime_ += scnMng_.GetDeltaTime();
		}
		else
		{
			isDelete_ = true;
		}
	}
	else
	{
		leaveInputTime_ = 0.0f;
	}
}
