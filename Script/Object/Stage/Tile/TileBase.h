#pragma once
#include "../../Common/Vector2.h"

class TileBase
{
public:
	
	// 種類
	enum class TYPE
	{
		NONE,		// なし
		BLOCK,		// ブロック
	};

	// パラメータ
	struct Parameter
	{
		int id = -1;
		TYPE type = TYPE::NONE;
		Vector2	position = Vector2(0, 0);
	};	
	
	// タイルのサイズ
	static constexpr int SIZE_TILE = 32;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TileBase(const Parameter& parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~TileBase();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init();
	
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// デバッグ描画
	/// </summary>
	virtual void DebugDraw();

private:

	// パラメータ情報
	Parameter parameter_;

};