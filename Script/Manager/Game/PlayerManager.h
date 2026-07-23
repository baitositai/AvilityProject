#pragma once
#include <vector>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2F.h"

class Player;
class ParameterPlayer;
class PlayerNewAccept;
class PlayerCheckAnnihilation;

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
	/// 全プレイヤーの活動状態を指定
	/// </summary>
	/// <param name="isActive">活動状態</param>
	void SetAllIsActive(const bool isActive);

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

	/// <summary>
	/// プレイヤーらの位置を返す
	/// </summary>
	/// <returns>プレイヤーらの位置</returns>
	const std::vector<Vector2F> GetPlayersPos() const;

	/// <summary>
	/// 最も近いプレイヤーのポインタを返す
	/// </summary>
	/// <param name="pos">基準となる位置</param>
	/// <returns>最も近いプレイヤー</returns>
	const Player* GetNearestPlayer(const Vector2F& pos) const;

	/// <summary>
	/// 指定された位置が右を向いているかどうかを判定します。
	/// </summary>
	/// <param name="pos">判定対象となる2次元座標。</param>
	/// <returns>右を向いている場合は true、そうでない場合は false を返します。</returns>
	bool IsLookRight(const Vector2F& pos) const;

	/// <summary>
	/// 全滅判定を返す
	/// </summary>
	/// <returns>全滅判定</returns>
	const bool IsPlayerAnnihilation() const { return isPlayerAnnihilation_; }

private:

	// プレイヤー残機
	int playersLeft_;

	// ゲームオーバー用カウントダウン
	float gameOverCountDown_;

	// 全滅判定
	bool isPlayerAnnihilation_;

	// 入力受付用の処理クラス
	std::unique_ptr<PlayerNewAccept> playerNewAccept_;

	// 全滅カウントダウン処理クラス
	std::unique_ptr<PlayerCheckAnnihilation> playerCheckAnnihilation_;

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