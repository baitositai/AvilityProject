#include <string>
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Object/Character/Enemy/EnemyClone.h"
#include "../../Object/Character/Enemy/EnemyMushroom.h"
#include "../../Object/Character/Enemy/EnemySlime.h"
#include "../../Object/Character/Enemy/EnemyHat.h"
#include "../../Object/Character/Enemy/EnemySnake.h"
#include "../../Object/Character/Enemy/EnemySamurai.h"
#include "../../Object/Common/Animation.h"
#include "../../System/EnemyGenerator.h"
#include "../Common/ResourceManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/SceneManager.h"
#include "EnemyManager.h"

void EnemyManager::Init()
{
	// 空の場合無視
	if (enemiesMap_.empty()) { return; }

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
	if (isStop_ || enemiesMap_.empty()) { return; }

	// 更新処理
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			// カメラ範囲内の場合
			auto& parameter = enemy->GetParameter();
			bool isInScreen = mainCamera.IsInScreenBox(parameter.pos_, parameter.hitSize_, parameter.angle_);
			if (isInScreen)
			{
				enemy->Update();
			}
			enemy->SetIsActive(isInScreen);
			
		}
	}
}

void EnemyManager::Draw()
{
	if (enemiesMap_.empty()) { return; }

	// 描画処理
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->Draw();
		}
	}
}

void EnemyManager::Sweep()
{
	for (auto& enemiesList : enemiesMap_)
	{
		auto it = std::remove_if(enemiesList.second.begin(), enemiesList.second.end(),
			[](const std::unique_ptr<EnemyBase>& enemy)
			{
				if (enemy == nullptr)
				{
					return true;
				}
				return enemy->IsDelete();
			});
		enemiesList.second.erase(it, enemiesList.second.end());
	}
}

void EnemyManager::DebugDraw()
{
	if (enemiesMap_.empty()) { return; }

	// 初期化
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->DebugDraw();
		}
	}
}

void EnemyManager::Generator(const std::vector<Vector2F>& createPositionList)
{
	using TYPE = EnemyTypes::TYPE;

	// 生成用のパラメータ情報を設定
	EnemyGenerator::Parameter parameter {};
	parameter.createCountMax = 2;
	parameter.createCountMin = 1;
	parameter.createPositionsList = createPositionList;
	parameter.createRange = Vector2F{ 128.0f, 64.0f };
	parameter.createEnemyTypeList = { TYPE::CLONE, TYPE::MUSHROOM, TYPE::SAMURAI, TYPE::SLIME, TYPE::SNAKE, TYPE::SLIME, TYPE::HAT };

	// 生成して格納
	auto addEnemyMap = enemyGenerator_->CreateEnemyMap(parameter);
	for (auto& enemies : addEnemyMap)
	{
		for (auto& enemy : enemies.second)
		{
			// 初期化
			enemy->Init();

			// 敵を格納
			enemiesMap_[enemies.first].push_back(std::move(enemy));
		}
	}
}

void EnemyManager::Create(const EnemyTypes::TYPE type, const Vector2F& pos)
{
	// 生成
	auto enemy = enemyGenerator_->CreateEnemy(type);

	// 位置調整
	enemy->GetParameter().pos_ = pos;

	// 格納
	enemiesMap_[type].push_back(std::move(enemy));
}

void EnemyManager::CreateBoss(const EnemyTypes::TYPE type, const Vector2F& pos)
{
	const int playerNum = PlayerManager::GetInstance().GetPlayerNum();

	// 生成
	auto enemy = enemyGenerator_->CreateEnemy(type);

	// 位置調整
	auto& param = enemy->GetParameter();
	param.pos_ = pos;

	// プレイヤー人数に応じたステータス補正
	// 2人目以降は1人増えるごとにHP50%、攻撃力20%加算
	constexpr float HP_SCALE_PER_PLAYER = 0.5f;
	constexpr float ATTACK_SCALE_PER_PLAYER = 0.2f;

	float hpRate = 1.0f + (playerNum - 1) * HP_SCALE_PER_PLAYER;
	float attackRate = 1.0f + (playerNum - 1) * ATTACK_SCALE_PER_PLAYER;

	// パラメータの設定
	param.hpMax_ = static_cast<int>(param.hpMax_ * hpRate);
	param.hp_ = param.hpMax_;
	param.attackPower_ = static_cast<int>(param.attackPower_ * attackRate);

	// 初期化
	enemy->Init();

	// 格納
	enemiesMap_[type].push_back(std::move(enemy));
}

void EnemyManager::CreateEventEnemy(const EnemyTypes::TYPE type, const Vector2F& pos)
{
	// 生成
	auto enemy = enemyGenerator_->CreateEnemy(type);

	// イベント管理用に生ポインタで保持
	EnemyBase* enemyPtr = enemy.get();

	// 位置調整
	auto& param = enemy->GetParameter();
	param.pos_ = pos;

	// ロジックの変更
	param.logicMap_.clear();
	param.logicMap_.emplace("chase", 1.0f);
	
	// 初期化
	enemy->Init();

	// 格納
	enemiesMap_[type].push_back(std::move(enemy));

	// イベント側でも監視対象として登録
	eventEnemyList_.push_back(enemyPtr);
}

void EnemyManager::CreateTutorialEnemy(const Vector2F& pos)
{
	// 生成
	auto enemy = enemyGenerator_->CreateEnemy(EnemyTypes::TYPE::SLIME);

	// 位置調整
	auto& param = enemy->GetParameter();
	param.pos_ = pos;

	// ロジックの変更
	param.logicMap_.clear();

	// 初期化
	enemy->Init();

	// アニメーションを再生
	enemy->GetAnimation().Play(Animation::TYPE::IDLE);

	// 格納
	enemiesMap_[EnemyTypes::TYPE::SLIME].push_back(std::move(enemy));
}

void EnemyManager::DestroyEventEnemy()
{
	for (auto& eventEnemy : eventEnemyList_)
	{
		eventEnemy->Delete();
	}
	eventEnemyList_.clear();
}

void EnemyManager::Clear()
{
	if (enemiesMap_.empty())
	{
		return;
	}

	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			if (enemy == nullptr)
			{
				continue;
			}
			enemy->Delete();
			enemy.reset();
		}
		enemiesList.second.clear();
	}
	enemiesMap_.clear();
}

void EnemyManager::CreateSandBagEnemy(const Vector2F& pos)
{
	// 生成
	auto enemy = enemyGenerator_->CreateEnemy(EnemyTypes::TYPE::GAIA_GOLEM);

	// 位置調整
	auto& param = enemy->GetParameter();
	param.pos_ = pos;

	// パラメータの設定
	param.hpMax_ = 9999;
	param.hp_ = param.hpMax_;
	param.attackPower_ = 0;

	// ロジックの変更
	param.logicMap_.clear();

	// 初期化
	enemy->Init();

	// アニメーションを再生
	enemy->GetAnimation().Play(Animation::TYPE::IDLE);

	// 格納
	enemiesMap_[EnemyTypes::TYPE::GAIA_GOLEM].push_back(std::move(enemy));
}

const bool EnemyManager::IsBossDestroy(const EnemyTypes::TYPE type) const
{
	// キーを探す
	auto it = enemiesMap_.find(type);

	// マップに存在しない場合は撃破された（あるいは存在しない）とみなす
	if (it == enemiesMap_.end())
	{
		return true;
	}

	// 空なら撃破
	return it->second.empty();
}

const bool EnemyManager::IsEmptyEventEnemies() 
{
	// 死亡済みのものを削除
	eventEnemyList_.erase(
		std::remove_if(eventEnemyList_.begin(), eventEnemyList_.end(),
			[](EnemyBase* enemy) { return enemy->IsDelete(); }),
		eventEnemyList_.end()
	);

	// 空か返す
	return eventEnemyList_.empty();
}

EnemyManager::EnemyManager()
{
	createBossEnemyType_ = EnemyTypes::TYPE::MAX;
	isStop_ = false;
	enemyGenerator_ = std::make_unique<EnemyGenerator>();
	enemyGenerator_->InitParameter();
}

EnemyManager::~EnemyManager()
{
}
