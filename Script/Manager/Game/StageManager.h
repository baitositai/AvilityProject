#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "../../Common/Vector2.h"

class TileBase;

class StageManager : public Singleton<StageManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<StageManager>;

public:

	// ステージの種類
	enum class TYPE
	{
		NONE,
		STAGE_FIRST,
		STAGE_SECOND,
		STAGE_THIRD,
		STAGE_BOSS,
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
	void Draw();

	/// <summary>
	/// ステージの変更
	/// </summary>
	/// <param name="type">種類</param>
	void ChageStage(const TYPE type);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// ステージのサイズを返す
	/// </summary>
	/// <returns>ステージのサイズ</returns>
	const Vector2& GetStageSize() const { return stageSize_; }

	/// <summary>
	/// タイルの列数と行数を返す
	/// </summary>
	/// <returns>タイルの列数と行数</returns>
	const Vector2& GetTileNums() const { return tileNums_; }

private:

	// 各種ステージごとのパス
	const std::unordered_map<TYPE, std::string> STAGE_PATH_MAP =
	{
		{ TYPE::STAGE_FIRST, "StageTest.csv" },
		{ TYPE::STAGE_SECOND, "StageSecond.csv" },
		{ TYPE::STAGE_THIRD, "StageThird.csv" },
		{ TYPE::STAGE_BOSS, "StageBoss.csv" },
	};

	// ステージサイズ
	Vector2 stageSize_;

	// タイル数
	Vector2 tileNums_;

	// 種類
	TYPE type_;

	// タイルの配列
	std::vector<std::vector<std::unique_ptr<TileBase>>> tiles_;

	// ステージの設定
	void SetStage();

	// ステージの初期化
	void ClearStage();

	// 描画範囲の取得
	void GetDrawRange(Vector2& rangeMin, Vector2& rangeMax);

	// コンストラクタ
	StageManager();

	// デストラクタ
	~StageManager();	
};

