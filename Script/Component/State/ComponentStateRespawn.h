#pragma once
#include <functional>
#include "ComponentCharacterStateBase.h"

class ParameterCharacter;
class SceneManager;
class CharacterBase;

class ComponentStateRespawn : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateRespawn(CharacterBase& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateRespawn() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 状態
	enum class STATE
	{
		READY,
		WAIT,
		MAX
	};

	// 待機時間
	static constexpr float RESPAWN_WAIT_TIME = 1.5f;

	// 所有者
	CharacterBase& owner_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 待機タイマー
	float waitTimer_;

	// 更新処理
	std::function<void()> update_;

	// パラメータ情報
	ParameterCharacter& parameter_;

	// 状態別更新処理
	void UpdateReady();
	void UpdateWait();
};