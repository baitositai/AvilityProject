#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "../../Common/Vector2.h"

class Stage;

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
	/// ステージサイズを返す
	/// </summary>
	/// <returns>ステージサイズ</returns>
	const Vector2& GetStageSize() const;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// 各種ステージごとのパス
	const std::unordered_map<TYPE, std::string> STAGE_PATH_MAP =
	{
		{ TYPE::NONE, "none" },
		{ TYPE::STAGE_FIRST, "StageTest.csv" },
		{ TYPE::STAGE_SECOND, "StageSecond.csv" },
		{ TYPE::STAGE_THIRD, "StageThird.csv" },
		{ TYPE::STAGE_BOSS, "StageBoss.csv" },
	};

	// 種類
	TYPE type_;

	// メインステージ
	std::unique_ptr<Stage> stage_;

	// コンストラクタ
	StageManager();

	// デストラクタ
	~StageManager();	
};

