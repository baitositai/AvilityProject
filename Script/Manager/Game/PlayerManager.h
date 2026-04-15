#pragma once
#include <vector>
#include "../../Template/Singleton.h"

class Player;

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

	// プレイヤーのリスト
	std::vector<std::unique_ptr<Player>> playerList_;

	// コンストラクタ
	PlayerManager();

	// デストラクタ
	~PlayerManager();
};