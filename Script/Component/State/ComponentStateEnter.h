#pragma once
#include <functional>
#include <unordered_map>
#include "ComponentCharacterStateBase.h"

class ComponentStateEnter : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateEnter(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateEnter() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// アニメーション時間
	static constexpr float ANIMATION_TIME = 1.8f;

	enum class STATE
	{
		START,
		WAIT,
		END,
	};

	// アニメーション時間
	float animationTime_;

	// 状態
	STATE state_;

	// 所有者
	CharacterBase& owner_;

	// 状態別更新
	std::function<void()> update_;

	// 状態別処理のマップ
	std::unordered_map<STATE, std::function<void()>> stateChangeMap_;

	// 状態別更新処理
	void UpdateStart();
	void UpdateWait();
	void UpdateEnd();

	// 状態変更処理
	void ChangeState(const STATE state);
	void ChangeStateStart();
	void ChangeStateWait();
	void ChangeStateEnd();
};

