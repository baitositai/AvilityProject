#pragma once
#include "../../Template/Singleton.h"

class PlayerManager : public Singleton<PlayerManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<PlayerManager>;

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
	PlayerManager();

	// デストラクタ
	~PlayerManager();

};

