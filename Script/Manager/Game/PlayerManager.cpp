#include <string>
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "../Common/ResourceManager.h"
#include "PlayerManager.h"

void PlayerManager::Init()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("PlayerParameter");
	const auto jsonParameter = jsonParameterMap.at("player").front();

	// プレイヤーのパラメータ
	auto parameter = std::make_unique<ParameterPlayer>();
	parameter->LoadParameter(jsonParameter);
	parameter->pos_ = { 200, 400 };

	// プレイヤーの生成
	playerList_.emplace_back(std::make_unique<Player>(std::move(parameter)));

	// 初期化
	for(const auto& player : playerList_)
	{
		player->Init();
	}
}

void PlayerManager::Update()
{
	for (const auto& player : playerList_)
	{
		player->Update();
	}
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
	for (const auto& player : playerList_)
	{
		player->DebugDraw();
	}
}

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}