#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "../../Common/Vector2.h"
#include "../Template/Singleton.h"

class Stage;
class GimmickBase;
class CharacterBase;
class BackGround;
class ParameterStage;

class StageManager : public Singleton<StageManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<StageManager>;

public:

	// ステージの種類
	enum class TYPE
	{
		NONE,	
		TRAIN,	// 電車
		BOSS,	// ボス部屋
		ROAD,	// ロード
		EVENT,	// イベント
		MAX,
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
	/// 生成
	/// </summary>
	/// <param name="type">種類</param>
	void Create(const TYPE type);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// ステージサイズを返す
	/// </summary>
	/// <returns>ステージサイズ</returns>
	const Vector2& GetStageSize() const;

	/// <summary>
	/// ボス部屋の座標を返す
	/// </summary>
	/// <returns></returns>
	const Vector2F& GetBossDoorPos();

	/// <summary>
	/// プレイヤーの初期位置を返す
	/// </summary>
	/// <returns>プレイヤーの初期位置</returns>
	const std::vector<Vector2F>& GetPlayerFirstPositions() const;

	/// <summary>
	/// 敵のエリア位置を返す
	/// </summary>
	/// <returns></returns>
	const std::vector<Vector2F>& GetEnemyAreaPositions() const;	
	
	// パラメータ関係の初期化
	void InitParameter();

private:

	// 各種ステージごとの名前パス
	const std::unordered_map<TYPE, std::string> STAGE_NAME_MAP =
	{
		{ TYPE::NONE, "none" },
		{ TYPE::TRAIN, "train" },
		{ TYPE::ROAD, "road" },
		{ TYPE::BOSS, "boss" },
		{ TYPE::EVENT, "event" },
	};

	// 種類
	TYPE type_;

	// タイルのチップサイズ
	Vector2 tileChipSize_;

	// メインステージ
	std::unique_ptr<Stage> stage_;

	// 背景
	std::vector<std::unique_ptr<BackGround>> backGrounds_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<TYPE, std::unique_ptr<ParameterStage>> templateParameterMap_;

	// 各種ステージ生成処理
	void CreateStageRoad();		// 自動生成の場合
	void CreateStageTrain();	// 電車シーンの場合
	void CreateStageRoom();		// 決められた部屋の場合
	void CreateStageCommon();	// 共通処理
	void CreateBackGround();	// 背景

	// コンストラクタ
	StageManager();

	// デストラクタ
	~StageManager() override;	
};

