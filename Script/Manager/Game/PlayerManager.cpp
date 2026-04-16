#include <string>
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/Player.h"
#include "../Common/ResourceManager.h"
#include "PlayerManager.h"

void PlayerManager::Init()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("PlayerParameter");
	const auto jsonPparameter = jsonParameterMap.at("player").front();

	// プレイヤーのパラメータ
	Player::Parameter parameter = {};
	parameter.scale = jsonPparameter["scale"].get<float>();
	parameter.angle = jsonPparameter["angle"].get<float>();
	parameter.direction = jsonPparameter["direction"].get<bool>();
	parameter.transparent = jsonPparameter["transparent"].get<bool>();
	parameter.moveSpeed = jsonPparameter["moveSpeed"].get<float>();
	parameter.divisionNum.x = jsonPparameter["divisionNum"]["x"].get<int>();
	parameter.divisionNum.y = jsonPparameter["divisionNum"]["y"].get<int>();
	parameter.hp = jsonPparameter["hp"].get<int>();
	parameter.attackPower = jsonPparameter["attackPower"].get<int>();
	std::vector<std::string> componentNameList = jsonPparameter["componentNameList"].get<std::vector<std::string>>();

	// リソースの取得
	ResourceManager& resourceManager = ResourceManager::GetInstance();

	// リソースを付与
	parameter.texuresHandle = resourceManager.GetHandles("player");

	// プレイヤーの生成
	playerList_.emplace_back(std::make_unique<Player>(parameter, componentNameList));

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
