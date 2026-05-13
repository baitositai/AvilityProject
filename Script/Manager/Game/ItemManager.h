#pragma once
#include <vector>
#include "../../Template/Singleton.h"

class ItemBase;

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
	/// 追加処理
	/// </summary>
	/// <param name="item">アイテム</param>
	void Add(std::unique_ptr<ItemBase> item);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// アイテムのリスト
	std::vector<std::unique_ptr<ItemBase>> itemList_;

	// コンストラクタ
	ItemManager();

	// デストラクタ
	~ItemManager();

};