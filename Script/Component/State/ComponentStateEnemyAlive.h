#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "ComponentCharacterStateBase.h"

class EnemyBase;
class ComponentLogicBase;
class SceneManager;

class ComponentStateEnemyAlive : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateEnemyAlive(EnemyBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateEnemyAlive() override;

	/// <summary>
	/// 生成処理
	/// </summary>
	void Create() override;

	/// <summary>
	/// 初期化処理
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

	// 状態
	enum class STATE
	{
		INTERVAL,
		LOGIC,
		MAX
	};

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 遅延タイマー
	float delayTimer_;

	// 状態
	STATE state_;

	// 更新処理
	std::function<void()> update_;

	// 状態遷移処理
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// 所有者
	EnemyBase& owner_;
	
	// 現在実行中のロジックのポインタ
	ComponentLogicBase* currentLogic_;

	// ロジック用のマップ
	std::unordered_map<std::string, std::unique_ptr<ComponentLogicBase>> componentLogicMap_;

	// 更新処理
	void UpdateInterval();
	void UpdateLogic();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateInterval();
	void ChangeStateLogic();

	// 次回のロジックを決定
	void SelectNextLogic();
};