#pragma once
#include <memory>
#include <random>
#include <functional>
#include <unordered_map>
#include "ComponentLogicBase.h"

class EnemyPanda;
class ParameterEnemyPanda;
class ColliderCircle;

class ComponentLogicBambooThrowing : public ComponentLogicBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentLogicBambooThrowing(EnemyPanda& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentLogicBambooThrowing() override;

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

	/// <summary>
	/// 攻撃のリセット
	/// </summary>
	void AttackReset() override;

private:	
	
	// 状態
	enum class STATE
	{
		ANIMATION,
		THROW,
		MAX
	};

	// 所有者
	EnemyPanda& owner_;

	// 所有者のパラメータ
	ParameterEnemyPanda& parameter_;

	// 攻撃位置
	Vector2F attackPos_;

	// 竹の投げる回数
	int bambooThrowCount_;

	// 攻撃判定
	bool isAttack_;

	// 状態
	STATE state_;

	// 乱数生成エンジン
	std::mt19937 randomCountEngine_;

	// 更新処理
	std::function<void()> update_;

	// 状態遷移の管理マップ
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// 攻撃コライダー
	std::shared_ptr<ColliderCircle> attackCollider_;

	// 更新処理
	void UpdateAnimation();
	void UpdateThrow();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateAnimation();
	void ChangeStateThrow();

	// 竹の生成
	void CreateBamboo();
};