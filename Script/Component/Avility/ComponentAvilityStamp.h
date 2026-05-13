#pragma once
#include <functional>
#include <unordered_map>
#include "ComponentAvilityBase.h"

class ColliderBox;

class ComponentAvilityStamp : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityStamp(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityStamp() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	enum class STATE
	{
		INPUT,		// 入力待ち
		STOP,		// 一時停止
		ACTIVE		// 落下
	};

	// 一時停止時間
	static constexpr float STOP_TIME = 0.5f;	

	// ジャンプ入力後から特定の時間後にスタンプを受け付ける
	static constexpr float INPUT_ENABLE_TIME = 0.1f;

	// 重力加速用
	static constexpr float ACC_GRAVITY = 16.0f;

	// 入力受付時間
	float inputEnableTime_;

	// 停止時間
	float stopTime_;

	// 重力保持用
	float gravity_;

	// 状態
	STATE state_;

	// 攻撃判定用コライダー
	std::shared_ptr<ColliderBox> attackCollider_;

	// 状態別更新
	std::function<void()> update_;

	// 状態別処理のマップ
	std::unordered_map<STATE, std::function<void()>> stateChangeMap_;

	// 状態別更新処理
	void UpdateInput();						
	void UpdateStop();						
	void UpdateActive();					

	// 状態変更処理
	void ChangeState(const STATE state);	
	void ChangeStateInput();
	void ChangeStateStop();
	void ChangeStateActive();

};