#pragma once
#include <vector>
#include "../Parameter/ParameterActor.h"
#include "../Common/Vector2.h"

class ItemManager;
class SceneManager;

class FoodShawer
{
public:

	struct Parameter
	{
		float interval_ = 0.0f;							// 食べ物が落ちてくる間隔
		int limitCount_ = -1;							// 制限数(ステージ上のアイテムで一定以上の場合は作らない)
		std::vector<ParameterActor::DIR> fallDirList_;	// 落下方向のリスト
		Vector2 createRangeTopLeft_;					// 作成範囲の左上
		Vector2 createRangeBottomRight_;				// 作成範囲の右下
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	FoodShawer(const Parameter& parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FoodShawer();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:

	// パラメータ情報
	Parameter parameter_;

	// アイテム管理クラス
	ItemManager& itemManager_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 生成感覚タイマー
	float createIntervalTimer_;

};