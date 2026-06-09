#pragma once
#include <functional>
#include "ComponentCharacterStateBase.h"

class SceneManager;
class Player;
class ParameterPlayer;

class ComponentStatePlayerSpawn : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerSpawn(Player& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerSpawn() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 待機時間
	static constexpr float RESPAWN_WAIT_TIME = 1.5f;

	// リスポーン条件の入力回数
	static constexpr int RESPAWN_CONDITION_INPUT_COUNT = 5;

	// 所有者
	Player& owner_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 待機タイマー
	float waitTimer_;

	// 更新処理
	std::function<void()> update_;

	// パラメータ情報
	ParameterPlayer& parameter_;

	// 状態別更新処理
	void UpdateReady();
	void UpdateWait();
};