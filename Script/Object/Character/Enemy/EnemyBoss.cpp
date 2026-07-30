#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Game/UiManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Ui/Enemy/UiBossHpBar.h"
#include "EnemyBoss.h"

EnemyBoss::EnemyBoss(std::unique_ptr<ParameterEnemyBoss> parameter) :
	EnemyBase(std::move(parameter))
{
	// パラメータ情報
	parameterEnemyBoss_ = dynamic_cast<ParameterEnemyBoss*>(GetParameterEnemyPtr());
	assert(parameterEnemyBoss_ != nullptr);
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::InitUi()
{
	uiMng_.Add(std::move(std::make_unique<UiBossHpBar>(*this)));
}

void EnemyBoss::DropItem()
{
	//ItemManager& itemManager = ItemManager::GetInstance();

	//// アイテムを生成する
	//itemManager.CreateMoneyItem(parameterEnemy_->dropMoney_, parameterEnemy_->pos_);

	//// 各アイテムのドロップ重み（数値を変更するだけで確率を簡単に調整できます）
	//const int WEIGHT_FOOD = 5;
	//const int WEIGHT_AVILITY = 3;
	//const int WEIGHT_TREASURE = 2;
	//const int WEIGHT_POTION = 4;
	//const int WEIGHT_NONE = 2; // アイテムなしの確率

	//// 重みの合計値を計算
	//const int TOTAL_WEIGHT = WEIGHT_FOOD + WEIGHT_AVILITY + WEIGHT_TREASURE + WEIGHT_POTION + WEIGHT_NONE;

	//// 範囲でランダム値を獲得
	//int randValue = GetRand(TOTAL_WEIGHT - 1);

	//// 累積確率による判定
	//if (randValue < WEIGHT_FOOD)
	//{
	//	itemManager.CreateFoodItem(static_cast<ItemTypes::FOOD_TYPE>(GetRand(ItemTypes::FOOD_TYPE_MAX - 1)), parameterEnemy_->pos_);
	//}
	//else if ((randValue -= WEIGHT_FOOD) < WEIGHT_AVILITY)
	//{
	//	itemManager.CreateAvilityItem(static_cast<AvilityTypes::TYPE>(GetRand(AvilityTypes::AVILITY_TYPE_MAX - 1)), parameterEnemy_->pos_);
	//}
	//else if ((randValue -= WEIGHT_AVILITY) < WEIGHT_TREASURE)
	//{
	//	itemManager.CreateTreasureItem(static_cast<ItemTypes::TREASURE_TYPE>(GetRand(ItemTypes::TREASURE_TYPE_MAX - 1)), parameterEnemy_->pos_);
	//}
	//else if ((randValue -= WEIGHT_TREASURE) < WEIGHT_POTION)
	//{
	//	itemManager.CreatePotionItem(static_cast<ItemTypes::POTION_TYPE>(GetRand(ItemTypes::POTION_TYPE_MAX - 1)), parameterEnemy_->pos_);
	//}

	GimmickManager::CreateParameter parameter = {};
	parameter.pos = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y + 100 };
	parameter.type = GimmickTypes::TYPE::TREASURE_CHEST;
	GimmickManager::GetInstance().Create(parameter);
}

void EnemyBoss::Dead()
{
	EnemyBase::Dead();

	sndMng_.PlaySe(SoundType::SE::BOSS_DESTROY);

	// ヒットストップ
	scnMng_.SetHitStop(0.75f);
}
