#include <string>
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Enemy/EnemyClone.h"
#include "../../Object/Common/Animation.h"
#include "../Common/ResourceManager.h"
#include "EnemyManager.h"

void EnemyManager::Init()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("EnemiesParameter");
	const auto jsonPparameter = jsonParameterMap.at("clone").front();

	// パラメータ
	EnemyClone::Parameter parameter = {};
	parameter.scale = jsonPparameter["scale"].get<float>();
	parameter.angle = jsonPparameter["angle"].get<float>();
	parameter.direction = jsonPparameter["direction"].get<bool>();
	parameter.transparent = jsonPparameter["transparent"].get<bool>();
	parameter.moveSpeed = jsonPparameter["moveSpeed"].get<float>();
	parameter.animationAttackSpeed = jsonPparameter["animationAttackSpeed"].get<float>();
	parameter.divisionNum.x = jsonPparameter["divisionNum"]["x"].get<int>();
	parameter.divisionNum.y = jsonPparameter["divisionNum"]["y"].get<int>();
	parameter.hp = jsonPparameter["hp"].get<int>();
	parameter.attackPower = jsonPparameter["attackPower"].get<int>();
	parameter.defaultAttackRadius = jsonPparameter["defaultAttackRadius"].get<int>();
	parameter.gravityPower = jsonPparameter["gravityPower"].get<float>();
	parameter.hitBoxSize = Vector2(jsonPparameter["hitBoxSize"]["x"].get<int>(), jsonPparameter["hitBoxSize"]["y"].get<int>());
	parameter.localPos = Vector2(jsonPparameter["localPos"]["x"].get<int>(), jsonPparameter["localPos"]["y"].get<int>());
	parameter.defaultAttackLocalPos = Vector2F(jsonPparameter["defaultAttackLoaclPos"]["x"].get<float>(), jsonPparameter["defaultAttackLoaclPos"]["y"].get<float>());
	parameter.weight = jsonPparameter["weight"].get<float>();
	parameter.pos = Vector2F(900.0f, 400.0f);

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

	// アニメーションの登録
	std::unique_ptr<Animation> animation = std::make_unique<Animation>();
	for (auto it = jsonPparameter["animation"].begin(); it != jsonPparameter["animation"].end(); ++it)
	{
		std::string animationName = it.key();
		auto& data = it.value();
		int start = data["no"].get<int>() * parameter.divisionNum.x;
		int end = data["num"].get<int>() + start - 1;
		float speed = data["speed"].get<float>();

		// アニメーション情報を格納
		animation->Add(animationName, start, end, speed);
	}

	// コンポーネントリストの取得
	std::vector<std::string> componentNameList = jsonPparameter["componentNameList"].get<std::vector<std::string>>();
	std::unordered_map<std::string, std::string> componentStateNameMap = jsonPparameter["componentStateNameList"].get<std::unordered_map<std::string, std::string>>();

	// リソースの取得
	ResourceManager& resourceManager = ResourceManager::GetInstance();

	// リソースを付与
	parameter.texuresHandle = resourceManager.GetHandles("clone");

	// 要素の型を CharacterBase にして宣言する
	std::vector<std::unique_ptr<CharacterBase>> enemies;

	// make_unique は EnemyClone で生成し、そのまま push_back する（ここでアップキャストされる）
	enemies.push_back(std::move(std::make_unique<EnemyClone>(parameter, componentStateNameMap, componentNameList, std::move(animation))));

	// 型が一致するため、正常に emplace できる
	enemiesMap_.emplace(TYPE::CLONE, std::move(enemies));

	// 初期化
	for (const auto& enemiesList : enemiesMap_)
	{
		for (const auto& enemy : enemiesList.second)
		{
			enemy->Init();
		}
	}
}

void EnemyManager::Update()
{
	// 更新処理
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->Update();
		}
	}
}

void EnemyManager::Draw()
{
	// 描画処理
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->Draw();
		}
	}
}

void EnemyManager::DebugDraw()
{
	// 初期化
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->DebugDraw();
		}
	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
