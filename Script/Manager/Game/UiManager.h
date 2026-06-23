#pragma once
#include <memory>
#include <functional>
#include <unordered_map>	
#include "../../Template/Singleton.h"

class UiBase;

class UiManager : public Singleton<UiManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<UiManager>;

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
	/// UIの追加処理
	/// </summary>
	/// <param name="ui"></param>
	void Add(std::unique_ptr<UiBase> ui);

	/// <summary>
	/// ゲーム画面用のUIを作成
	/// </summary>
	void CreateGameUi();

	/// <summary>
	/// 削除処理
	/// </summary>
	void Sweep();

	/// <summary>
	/// クリア処理
	/// </summary>
	void Clear();

private:

	// UIリスト
	std::vector<std::unique_ptr<UiBase>> uiList_;
	
	// コンストラクタ
	UiManager();

	// デストラクタ
	~UiManager();
};