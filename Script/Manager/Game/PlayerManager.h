#pragma once
#include <vector>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2F.h"

class Player;
class ParameterPlayer;
class PlayerNewAccept;

class PlayerManager : public Singleton<PlayerManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<PlayerManager>;

public:

	// プレイヤー最大人数
	static constexpr int PLAYER_MAX = 4;

	// プレイヤー残機最大数
	static constexpr int PLAYER_LEFT = 5;

	// プレイヤー残機加算数
	static constexpr int DEFAULT_ADD_PLAYER_LEFT = -1;

	/// <summary>
	/// プレイヤー生成
	/// </summary>
	void Create();

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
	/// 削除処理
	/// </summary>
	void Clear();

	/// <summary>
	/// 準備処理
	/// </summary>
	void Ready();

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 全プレイヤーの持つアイテムをデタッチ
	/// </summary>
	void AllDetachItem();

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

	/// <summary>
	/// プレイヤーの残機追加
	/// </summary>
	/// <param name="addLeft">追加残機</param>
	void AddPlayersLeft(const int addLeft = DEFAULT_ADD_PLAYER_LEFT);

	/// <summary>
	/// プレイヤー残機を返す
	/// </summary>
	/// <returns>プレイヤー残機</returns>
	const int GetPlayerLeft() const { return playersLeft_; }

	/// <summary>
	/// プレイヤー人数を返す
	/// </summary>
	/// <returns>プレイヤー人数</returns>
	const int GetPlayerNum() const;

	/// <summary>
	/// 盗んだお宝の合計金額を返す
	/// </summary>
	/// <returns>合計金額</returns>
	const int GetTotalLootTreasuresMoney() const;

private:

	// プレイヤー残機
	int playersLeft_;

	// 入力受付用の処理クラス
	std::unique_ptr<PlayerNewAccept> playerNewAccept_;

	// テンプレートとなるパラメータ
	std::unique_ptr<ParameterPlayer> templateParameter_;

	// プレイヤーのリスト
	std::vector<std::unique_ptr<Player>> playerList_;

	// 新規プレイヤーの受付
	void AcceptNewPlayer();

	// ゲームの退出
	void LeavePlayer();

	// コンストラクタ
	PlayerManager();

	// デストラクタ
	~PlayerManager();
};