#pragma once
#include <string>
#include <functional>
#include "../../Common/Vector2F.h"

class BackGround
{
public:
	
	enum class TYPE
	{
		FIX,
		SCROLL,
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BackGround();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BackGround();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	
	/// <summary>
	/// 種類の設定
	/// </summary>
	/// <param name="type">種類</param>
	void SetType(const TYPE type);

	/// <summary>
	/// リソースの設定
	/// </summary>
	/// <param name="key">リソース呼び出し用のキー</param>
	void SetResource(const std::string& key);

private:

	// リソース
	int img_;

	// スクロール速度
	float scrollSpeed_;

	// 座標
	Vector2F pos_;

	// スクロール用サブ座標
	Vector2F subPos_;

	// 更新処理
	std::function<void()> update_;

	// 描画処理
	std::function<void()> draw_;

	// 種類別更新処理
	void UpdateFix();
	void UpdateScroll();

	// 種類別描画処理
	void DrawFix();
	void DrawScroll();
};

