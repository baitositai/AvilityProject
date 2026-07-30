#pragma once
#include <vector>
#include <unordered_map>
#include "../../Template/Singleton.h"
#include "../../Manager/Game/ItemTypes.h"
#include "../../Component/Avility/AvilityTypes.h"
#include "../../Parameter/ParameterActor.h"
#include "../../Scene/SceneShop.h"

class ItemBase;
class ItemGenerator;

class ItemManager : public Singleton<ItemManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<ItemManager>;

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 削除処理
	/// </summary>
	void Sweep();

	/// <summary>
	/// 持ち越しとクリア
	/// </summary>
	void CarryAndClear();

	/// <summary>
	/// 全てのアイテムに持ち越し判定を設定する
	/// </summary>
	/// <param name="isCarry">持ち越し判定</param>
	void SetAllIsCarry(const bool isCarry);

	/// <summary>
	/// クリア処理
	/// </summary>
	void Clear();

	/// <summary>
	/// 追加処理
	/// </summary>
	/// <param name="item">アイテム</param>
	void Add(std::unique_ptr<ItemBase> item);

	/// <summary>
	/// アビリティアイテムの生成
	/// </summary>
	/// <param name="type">種類</param>
	void CreateAvilityItem(const AvilityTypes::TYPE type, const Vector2F& pos);

	/// <summary>
	/// 食べ物の生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="fallDir">落下方向</param>
	void CreateFoodItem(const ItemTypes::FOOD_TYPE type, const Vector2F& pos, const ParameterActor::DIR fallDir = ParameterActor::DIR::DOWN);

	/// <summary>
	/// お宝の生成
	/// </summary>
	/// <param name="type">種類</param>
	void CreateTreasureItem(const ItemTypes::TREASURE_TYPE type, const Vector2F& pos);

	/// <summary>
	/// ポーションの生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="pos">座標</param>
	void CreatePotionItem(const ItemTypes::POTION_TYPE type, const Vector2F& pos);

	/// <summary>
	/// 金額分お金アイテムを生成
	/// </summary>
	/// <param name="moneyAmount">金額</param>
	void CreateMoneyItem(const int moneyAmount, const Vector2F& pos);

	/// <summary>
	/// 宝箱用のアイテムの生成
	/// </summary>
	void CreateTreasureChestItems(const Vector2F& tresureChestPos);

	/// <summary>
	/// アイテム群の生成
	/// </summary>
	/// <param name="itemList">生成リスト</param>
	void CreateItemList(const std::vector<Vector2F>& itemList);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 指定したアイテムの数を返す
	/// </summary>
	/// <returns>アイテム数</returns>
	const int GetItemCount(const ItemTypes::TYPE type) const;

	/// <summary>
	/// 最も距離の近い食べ物を返す
	/// </summary>
	/// <param name="basePos">調べる位置</param>
	/// <returns>食べ物</returns>
	ItemBase* GetNearestFood(const Vector2F& basePos);

	/// <summary>
	/// 展示品をランダムで決定・情報を返す
	/// </summary>
	/// <param name="abilityNum">アビリティの生成数</param>
	/// <param name="potionNum">ポーションの生成数</param>
	/// <param name="foodNum">食べ物の生成数</param>
	/// <returns>展示品の配列</returns>
	std::vector<SceneShop::Exhibits> GetRandomExhibits(const int abilityNum, const int potionNum, const int foodNum);

	/// <summary>
	/// 能力お試し部屋のアイテム生成
	/// </summary>
	/// <param name="itemList">座標リスト</param>
	void CreateAbilityTrial(const std::vector<Vector2F>& itemList);

	/// <summary>
	/// 能力お試し部屋のチェック処理
	/// </summary>
	void CheckAbilityTrial();

private:

	// 座標リスト
	std::unordered_map<AvilityTypes::TYPE, Vector2F> abilityTrialPositionMap_;

	// アイテムのリスト
	std::unordered_map<ItemTypes::TYPE, std::vector<std::unique_ptr<ItemBase>>> itemMap_;

	// アイテムの生成
	std::unique_ptr<ItemGenerator> itemGenerator_;

	// コンストラクタ
	ItemManager();

	// デストラクタ
	~ItemManager();
};