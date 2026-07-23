#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/Input.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/FontManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "../../System/PlayerNewAccept.h"
#include "../../System/PlayerCheckAnnihilation.h"
#include "../Common/ResourceManager.h"
#include "../Game/GameManager.h"
#include "PlayerManager.h"

void PlayerManager::Create()
{	
	// 空じゃない場合
	if (!playerList_.empty())
	{
		// 中身をけす
		Clear();
	}

	// パッドの接続数空プレイヤー生成数を取得
	int playerCount = GetJoypadNum();

	// パッドの接続がない場合プレイヤー数1人
	if (playerCount < 1) { playerCount = 1; }

	// プレイヤーを生成する
	for (int i = 0; i < playerCount; i++)
	{
		// パラメータ取得
		auto parameter = std::make_unique<ParameterPlayer>(*templateParameter_);
		parameter->resourceKey_ += std::to_string(i + 1);
		parameter->padNo_ = static_cast<Input::JOYPAD_NO>(i + 1);
		
		// プレイヤーの生成
		playerList_.emplace_back(std::make_unique<Player>(std::move(parameter)));
	}
}

void PlayerManager::Init()
{
	// 初期化
	if (!playerList_.empty())
	{
		for (const auto& player : playerList_)
		{
			player->Init();
		}
	}

	// プレイ中の新規受付処理
	playerNewAccept_ = std::make_unique<PlayerNewAccept>();
	playerNewAccept_->Init(static_cast<int>(playerList_.size()));

	// プレイヤーの全滅カウントダウン処理
	playerCheckAnnihilation_ = std::make_unique<PlayerCheckAnnihilation>();
	playerCheckAnnihilation_->Init();

	// プレイヤー残機
	playersLeft_ = PLAYER_LEFT;
}

void PlayerManager::Update()
{
	// 全滅判定を有効
	isPlayerAnnihilation_ = true;

	// プレイヤー処理
	for (const auto& player : playerList_)
	{
		if (!player->IsActive())
		{
			continue;
		}

		player->Update();

		// 生存している場合
		if (player->GetState() != Player::STATE::DEAD)
		{
			// 判定を無効
			isPlayerAnnihilation_ = false;
		}
	}

	// プレイヤーの新規受付処理
	AcceptNewPlayer();

	// プレイヤーの退出処理
	LeavePlayer();

	// カウントダウン処理
	playerCheckAnnihilation_->Update();
}

void PlayerManager::Draw()
{
	for (const auto& player : playerList_)
	{
		player->Draw();
	}
}

void PlayerManager::Clear()
{
	for (const auto& player : playerList_)
	{
		player->Delete();
	}
	playerList_.clear();
}

void PlayerManager::Sweep()
{
	// 終了したプレイヤーを並び変える
	auto it = std::remove_if(playerList_.begin(), playerList_.end(),
		[](const std::unique_ptr<Player>& player)
		{
			return player->IsDelete();
		});

	// 終了したプレイヤーを削除する
	playerList_.erase(it, playerList_.end());
}

void PlayerManager::Ready()
{
	for (const auto& player : playerList_)
	{
		player->Ready();
	}
}

void PlayerManager::DebugDraw()
{
	for (const auto& player : playerList_)
	{
		player->DebugDraw();
	}
}

void PlayerManager::AllDetachItem()
{
	for (const auto& player : playerList_)
	{
		player->DetachItem();
	}
}

const Vector2F& PlayerManager::GetCameraFollowPos() const
{
	// 1Pの座標を返す
	return playerList_.front()->GetParameter().pos_;
}

void PlayerManager::SetFirstPositions(const std::vector<Vector2F>& positions)
{
	// プレイヤー人数が初期位置の数より多い場合終了
	if (playerList_.size() > positions.size()) { return; }

	int playerNum = static_cast<int>(playerList_.size());
	for (int i = 0; i < playerNum; i++)
	{
		playerList_[i]->GetParameter().pos_ = positions[i];
	}
}

void PlayerManager::AddPlayersLeft(const int addLeft)
{
	// プレイヤー残機追加
	playersLeft_ += addLeft;

	// 残機が0未満の場合
	if (playersLeft_ < 1)
	{
		// プレイヤー1が死亡状態の場合
		if (playerList_.front()->GetState() == Player::STATE::DEAD)
		{
			// ゲームオーバーへ
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
		}

		// 残機は0へ
		playersLeft_ = 0;
	}
}

void PlayerManager::SetAllIsActive(const bool isActive)
{
	for (auto& player : playerList_)
	{
		player->SetIsActive(isActive);
	}
}

const int PlayerManager::GetPlayerNum() const
{
	return static_cast<int>(playerList_.size());
}

void PlayerManager::AcceptNewPlayer()
{
	// 新しいパッドからの参加入力があった場合
	const int padNo = playerNewAccept_->IsNewPlayerAccept();
	if (padNo > -1)
	{
		// プレイヤーを生成する
		auto parameter = std::make_unique<ParameterPlayer>(*templateParameter_);

		// 個別パラメータの設定
		parameter->padNo_ = static_cast<Input::JOYPAD_NO>(padNo);
		parameter->resourceKey_ = "player" + std::to_string(padNo);

		// 残機がない場合HPを10分の1にする
		if (playersLeft_ < 1) { parameter->hp_ /= 10; }
		
		// 初期位置を画面真ん中に生成
		parameter->pos_ = Vector2F::SubVector2F(Vector2F((float)Application::SCREEN_HALF_X, (float)Application::SCREEN_HALF_Y), mainCamera.GetPos());

		// プレイヤーの生成
		auto newPlayer = std::make_unique<Player>(std::move(parameter));
		newPlayer->Init();
		playerList_.emplace_back(std::move(newPlayer));
	}
}

void PlayerManager::LeavePlayer()
{
	int playerListSize = static_cast<int>(playerList_.size());

	// 参加者が複数人いない場合
	if (playerListSize < 2)
	{
		return;
	}

	// 2Pから開始
	for (int i = 1; i < playerListSize; ++i)
	{
		if (playerList_[i]->IsDelete())
		{
			// 受付パッドを追加
			playerNewAccept_->SetPadNo(static_cast<int>(playerList_[i]->GetParameter().padNo_));

			// 削除要求のみを行う
			playerList_[i]->Delete();
		}
	}
}

const int PlayerManager::GetTotalLootTreasuresMoney() const
{
	int total = 0;
	for (const auto& player : playerList_)
	{
		total += player->GetTotalLootTreasuresMoney();
	}
	return total;
}

const std::vector<Vector2F> PlayerManager::GetPlayersPos() const
{
	std::vector<Vector2F> playersPos;
	for (const auto& player : playerList_)
	{
		playersPos.push_back(player->GetParameter().pos_);
	}
	return playersPos;
}

const Player* PlayerManager::GetNearestPlayer(const Vector2F& pos) const
{
	// 空の場合は即終了
	if (playerList_.empty())
	{
		return nullptr;
	}

	// 空のポインタを用意	
	Player* nearestPlayer = nullptr;

	// 人数を取得
	const int playerNum = static_cast<int>(playerList_.size());

	// 1Pの場合はそのまま返す
	if (playerNum == 1)
	{
		nearestPlayer = playerList_.front().get();
	}
	else 	
	{
		float minDistanceSq = FLT_MAX;
		for (const auto& player : playerList_)
		{
			Vector2F diff = Vector2F::SubVector2F(player->GetParameter().pos_, pos);
			float distSq = diff.x * diff.x + diff.y * diff.y;
			if (distSq < minDistanceSq)
			{
				minDistanceSq = distSq;
				nearestPlayer = player.get();
			}
		}
	}
	return nearestPlayer;
}

bool PlayerManager::IsLookRight(const Vector2F& pos) const
{
	if (playerList_.empty())
	{
		return false;
	}

	// 一番近いプレイヤーを探す
	Vector2F closestPlayerPos = {};
	float minDistanceSq = -1.0f;

	for (const auto& player : playerList_)
	{
		Vector2F playerPos = player->GetParameter().pos_;

		// 距離の2乗を計算
		float dx = playerPos.x - pos.x;
		float dy = playerPos.y - pos.y;
		float distanceSq = dx * dx + dy * dy;

		if (minDistanceSq < 0.0f || distanceSq < minDistanceSq)
		{
			minDistanceSq = distanceSq;
			closestPlayerPos = playerPos;
		}
	}

	// 向きの決定
	if (pos.x < closestPlayerPos.x)
	{
		return true;
	}

	return false;
}

PlayerManager::PlayerManager()
{	
	playersLeft_ = -1;	
	isPlayerAnnihilation_ = false;

	// 初回のみ外部データを読み込んでテンプレートを作成
	if (!templateParameter_)
	{
		const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("PlayerParameter");
		const auto jsonParameter = jsonParameterMap.at("player").front();

		templateParameter_ = std::make_unique<ParameterPlayer>();
		templateParameter_->LoadParameter(jsonParameter);
	}
}

PlayerManager::~PlayerManager()
{
}