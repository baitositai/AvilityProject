#pragma once
#include <functional>
#include "../Component/State/ComponentCharacterStateBase.h"

class CharacterBase;
class InputManager;

class ComponentStateDead :  public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateDead(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateDead() override;

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
	CharacterBase& owner_;

	// 入力管理クラスの参照
	InputManager& inputManager_;

	// 状態別更新処理
	void UpdateAnimation();
	void UpdateRespownAccept();
};