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

	enum class LAYER
	{
		SPEECH_BUBBLE,	// 先に描画
		UI,				// 後に描画
		MAX
	};

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
	/// <param name="layer">レイヤー</param>
	void Draw(const LAYER layer);

	/// <summary>
	/// UIの追加処理
	/// </summary>
	/// <param name="ui">UI</param>
	/// <param name="layer">レイヤー種類</param>
	void Add(std::unique_ptr<UiBase> ui, const LAYER layer = LAYER::UI);

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

	/// <summary>
	/// 活動状態の設定
	/// </summary>
	/// <param name="isActive">活動状態</param>
	/// <param name="layer">レイヤー</param>
	void SetAllIsActive(const bool isActive, const LAYER layer = LAYER::UI);

private:

	// UIリスト
	std::unordered_map<LAYER, std::vector<std::unique_ptr<UiBase>>> uiMap_;
	
	// コンストラクタ
	UiManager();

	// デストラクタ
	~UiManager();
};