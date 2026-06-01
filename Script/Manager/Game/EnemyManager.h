#pragma once
#include <vector>
#include <unordered_map>
#include "../../Template/Singleton.h"

class EnemyBase;
class ParameterEnemy;

class EnemyManager : public Singleton<EnemyManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<EnemyManager>;

public:

	// 種類
	enum class TYPE
	{
		CLONE,
		SLIME,
		MUSHROOM,
		HAT,
		SNAKE,
		SAMURAI,
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
	/// 削除処理
	/// </summary>
	void Sweep();

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 削除
	/// </summary>
	void Clear();

private:

	// 敵を管理するマップ
	std::unordered_map<TYPE, std::vector<std::unique_ptr<EnemyBase>>> enemiesMap_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<TYPE, std::unique_ptr<ParameterEnemy>> templateParameterMap_;

	// パラメータの初期化処理
	void InitParameter();

	// コンストラクタ
	EnemyManager();

	// デストラクタ
	~EnemyManager();
};
