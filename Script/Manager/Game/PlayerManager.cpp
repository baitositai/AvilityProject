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
	parameter.animationSpeed = jsonPparameter["animationSpeed"].get<float>();
	parameter.divisionNum.x = jsonPparameter["divisionNum"]["x"].get<int>();
	parameter.divisionNum.y = jsonPparameter["divisionNum"]["y"].get<int>();
	parameter.hp = jsonPparameter["hp"].get<int>();
	parameter.jumpPow = jsonPparameter["jumpPowerMax"].get<float>();
	parameter.jumpPowMax = jsonPparameter["jumpPowerMax"].get<float>();
	parameter.dashSpeed = jsonPparameter["dashSpeed"].get<float>();
	parameter.attackPower = jsonPparameter["attackPower"].get<int>();
	parameter.gravityPower = jsonPparameter["gravityPower"].get<float>();
	parameter.hitBoxSize = Vector2(jsonPparameter["hitBoxSize"]["x"].get<int>(), jsonPparameter["hitBoxSize"]["y"].get<int>());
	parameter.localPos = Vector2(jsonPparameter["loacalPos"]["x"].get<int>(), jsonPparameter["loacalPos"]["y"].get<int>());
	parameter.weight = jsonPparameter["weight"].get<float>();
	parameter.pos = Vector2F(400.0f, 400.0f);

	// アニメーションの登録
	parameter.animationsIdle = jsonPparameter["animationsIdle"].get<int>();
	parameter.animationsWalk = jsonPparameter["animationsWalk"].get<int>();
	parameter.animationsBrake = jsonPparameter["animationsBrake"].get<int>();
	parameter.animationsAttack = jsonPparameter["animationsAttack"].get<int>();
	parameter.animationsJump = jsonPparameter["animationsJump"].get<int>();
	parameter.animationsFall = jsonPparameter["animationsFall"].get<int>();
	parameter.animationsDie = jsonPparameter["animationsDie"].get<int>();
	parameter.animationsDamage = jsonPparameter["animationsDamage"].get<int>();
	parameter.animationsPause = jsonPparameter["animationsPause"].get<int>();

	// コンポーネントリストの取得
	std::vector<std::string> componentNameList = jsonPparameter["componentNameList"].get<std::vector<std::string>>();
	std::unordered_map<std::string, std::string> componentStateNameMap = jsonPparameter["componentStateNameList"].get<std::unordered_map<std::string, std::string>>();

	// リソースの取得
	ResourceManager& resourceManager = ResourceManager::GetInstance();

	// リソースを付与
	parameter.texuresHandle = resourceManager.GetHandles("player");

	// プレイヤーの生成
	playerList_.emplace_back(std::make_unique<Player>(parameter, componentStateNameMap, componentNameList));

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
