#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "ComponentAvilityBase.h"

class ComponentAvilityTeleport : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityTeleport(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityTeleport() override;

	/// <summary>
	/// 生成処理
	/// </summary>
	void Create() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 取り外し処理
	/// </summary>
	void Remove() override;

private:

	enum class STATE
	{
		INPUT,		// 入力待ち
		MOVE,		// 移動処理
		APPEAR		// 出現
	};

	// 追加攻撃力
	static constexpr int ADD_ATTACK_POWER = 50;

	// 移動制限時間
	static constexpr float MOVE_TIME = 1.0f;

	// 状態遷移時間
	static constexpr float CHANGE_TIME = 0.3f;

	// 終了後の無敵時間
	static constexpr float FINISH_INVICIBLE_TIME = 0.05f;

	// 移動制限用タイマー
	float moveTimer_;

	// 状態遷移用タイマー
	float changeTimer_;

	// 状態
	STATE state_;

	// 状態別更新
	std::function<void()> update_;

	// 状態別処理のマップ
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// 状態別更新処理
	void UpdateInput();
	void UpdateMove();
	void UpdateAppear();

	// 状態変更処理
	void ChangeState(const STATE state);
	void ChangeStateInput();
	void ChangeStateMove();
	void ChangeStateAppear();
};