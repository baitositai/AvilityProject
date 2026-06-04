#pragma once
#include <vector>
#include <unordered_map>
#include "../../Template/Singleton.h"
#include "EnemyTypes.h"

class EnemyBase;
class EnemyGenerator;

class EnemyManager : public Singleton<EnemyManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<EnemyManager>;

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
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="createPositionList">生成位置を格納したリスト</param>
	void Generator(const std::vector<Vector2F>& createPositionList);

	/// <summary>
	/// 削除
	/// </summary>
	void Clear();	

private:

	// 敵の生成に関するジェネレーター
	std::unique_ptr<EnemyGenerator> enemyGenerator_;

	// 敵を管理するマップ
	std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> enemiesMap_;

	// コンストラクタ
	EnemyManager();

	// デストラクタ
	~EnemyManager();
};
