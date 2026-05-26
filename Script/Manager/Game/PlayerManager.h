#pragma once
#include <vector>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2F.h"

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

	/// <summary>
	/// カメラの追従を行う座標を返す
	/// </summary>
	/// <returns>追従対象の座標</returns>
	const Vector2F& GetCameraFollowPos() const;

	/// <summary>
	/// 初期位置を設定
	/// </summary>
	/// <param name="positions">位置情報</param>
	void SetFirstPositions(const std::vector<Vector2F>& positions);

private:

	// プレイヤーのリスト
	std::vector<std::unique_ptr<Player>> playerList_;

	// コンストラクタ
	PlayerManager();

	// デストラクタ
	~PlayerManager();
};