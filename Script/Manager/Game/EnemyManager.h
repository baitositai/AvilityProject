#pragma once
#include "../../Template/Singleton.h"

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
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// コンストラクタ
	EnemyManager();

	// デストラクタ
	~EnemyManager();
};
