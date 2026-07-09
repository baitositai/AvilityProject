#pragma once
#include "ComponentCharacterStateBase.h"

class Player;
class InputManager;

class ComponentStatePlayerDead : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner"></param>
	ComponentStatePlayerDead(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerDead() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	enum class STATE
	{
		ANIMATION,		// アニメーション処理
		RESPOWN_ACCEPT,	// 復活受付
		MAX
	};

	// リスポーン条件の入力回数
	static constexpr int RESPAWN_CONDITION_INPUT_COUNT = 5;

	// リスポーン受付値
	int respownValue_;

	// 更新処理
	std::function<void()> update_;

	// 所有者
	Player& owner_;

	// 入力管理クラスの参照
	InputManager& inputManager_;

	// 状態別更新処理
	void UpdateStart();
	void UpdateAnimation();
	void UpdateRespownAccept();
};