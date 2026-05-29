#include <string>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/FontManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "../../System/PlayerNewAccept.h"
#include "../Common/ResourceManager.h"
#include "../Game/GameManager.h"
#include "PlayerManager.h"

void PlayerManager::Init()
{
	// 初回のみ外部データを読み込んでテンプレートを作成
	if (!templateParameter_)
	{
		const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("PlayerParameter");
		const auto jsonParameter = jsonParameterMap.at("player").front();

		templateParameter_ = std::make_unique<ParameterPlayer>();
		templateParameter_->LoadParameter(jsonParameter);
	}

	// プレイヤーを生成する
	auto parameter = std::make_unique<ParameterPlayer>(*templateParameter_);
	parameter->resourceKey_ += std::to_string(1);

	// プレイヤーの生成
	playerList_.emplace_back(std::make_unique<Player>(std::move(parameter)));

	// 初期化
	for (const auto& player : playerList_)
	{
		player->Init();
	}

	// プレイ中の新規受付処理
	playerNewAccept_ = std::make_unique<PlayerNewAccept>();
	playerNewAccept_->Init(static_cast<int>(playerList_.size()));

	// プレイヤー残機
	playersLeft_ = PLAYER_LEFT;

	// フォント
	font_ = FontManager::GetInstance().CreateMyFont(L"ベストテンDOT", 48, 3);
}

void PlayerManager::Update()
{
	// プレイヤー処理
	for (const auto& player : playerList_)
	{
		player->Update();
	}

	// プレイヤーの新規受付処理
	AcceptNewPlayer();

	// プレイヤーの退出処理
	LeavePlayer();
}

void PlayerManager::Draw()
{
	for (const auto& player : playerList_)
	{
		player->Draw();
	}
}

void PlayerManager::DebugDraw()
{
	DrawFormatStringToHandle(0, 0, UtilityCommon::WHITE, font_, L"YOUR LIFE %d", playersLeft_);
	for (const auto& player : playerList_)
	{
		player->DebugDraw();
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

	// 1Pが死亡したかつ残機が0未満の場合
	if (playerList_.front()->GetState() == Player::STATE::DEAD &&
		playersLeft_ < 0)
	{
		// ゲームオーバーへ遷移
		GameManager::GetInstance().GameOver();
	}
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

		// 残機がない場合HPを5分の1にする
		if (playersLeft_ < 1) { parameter->hp_ /= 5; }
		
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
	if (playerList_.size() < 2)
	{
		return;
	}

	// 2Pから開始
	auto it = playerList_.begin() + 1;

	while (it != playerList_.end())
	{
		if ((*it)->IsDelete())
		{
			// 受付パッドを追加
			playerNewAccept_->SetPadNo(static_cast<int>((*it)->GetParameter().padNo_));

			(*it)->Delete();

			// 削除された次の要素のイテレータを返す
			it = playerList_.erase(it);
		}
		else
		{
			// インテレータを進める
			++it;
		}
	}
}

PlayerManager::PlayerManager()
{
	font_ = -1;
	playersLeft_ = -1;
}

PlayerManager::~PlayerManager()
{
}