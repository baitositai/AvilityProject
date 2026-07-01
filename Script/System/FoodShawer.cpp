#include "../Utility/UtilityCommon.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Game/ItemManager.h"
#include "FoodShawer.h"

FoodShawer::FoodShawer(const Parameter& parameter) :
	parameter_(parameter),
	itemManager_(ItemManager::GetInstance()),
	sceneManager_(SceneManager::GetInstance())
{
	createIntervalTimer_ = 0.0f;
}

FoodShawer::~FoodShawer()
{
}

void FoodShawer::Init()
{
	// 初期化処理
	createIntervalTimer_ = 1.0f;
}

void FoodShawer::Update()
{
	// アイテムの数が制限以上の場合は生成しない
	if(itemManager_.GetItemCount(ItemTypes::TYPE::FOOD) >= parameter_.limitCount_ && parameter_.limitCount_ != -1)
	{
		return;
	}

	// 更新処理
	createIntervalTimer_ -= sceneManager_.GetDeltaTime();

	// 生成間隔を超えた場合
	if(createIntervalTimer_ <= 0.0f)
	{
		// 落下方向のランダム取得
		const int randomIndex = UtilityCommon::GetRandomCount(0, static_cast<int>(parameter_.fallDirList_.size()) - 1);
		const ParameterActor::DIR fallDir = parameter_.fallDirList_[randomIndex];

		// 作成範囲のランダム取得
		const int randomX = UtilityCommon::GetRandomCount(parameter_.createRangeTopLeft_.x, parameter_.createRangeBottomRight_.x);
		const int randomY = UtilityCommon::GetRandomCount(parameter_.createRangeTopLeft_.y, parameter_.createRangeBottomRight_.y);
		Vector2 createPos = { randomX, randomY };

		// 食べ物の生成
		itemManager_.CreateFoodItem(static_cast<ItemTypes::FOOD_TYPE>(UtilityCommon::GetRandomCount(0, ItemTypes::FOOD_TYPE_MAX - 1)), createPos.ToVector2F(), fallDir);
		
		// タイマーリセット
		createIntervalTimer_ = parameter_.interval_;
	}
}