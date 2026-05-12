#pragma once
#include <vector>
#include <unordered_map>
#include "../../Template/Singleton.h"

class CharacterBase;

class EnemyManager : public Singleton<EnemyManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<EnemyManager>;

public:

	// 種類
	enum class TYPE
	{
		CLONE,
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
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// 敵を管理するマップ
	std::unordered_map<TYPE, std::vector<std::unique_ptr<CharacterBase>>> enemiesMap_;

	// コンストラクタ
	EnemyManager();

	// デストラクタ
	~EnemyManager();
};
