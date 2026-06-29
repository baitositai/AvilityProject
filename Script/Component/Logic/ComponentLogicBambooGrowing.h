#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "ComponentLogicBase.h"

class EnemyPanda;
class ParameterEnemyPanda;
class ColliderCircle;

class ComponentLogicBambooGrowing : public ComponentLogicBase
{
public:


	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentLogicBambooGrowing(EnemyPanda& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentLogicBambooGrowing() override;

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

	// 竹の生成インターバル
	static constexpr float INTERVAL_TIME = 0.05f;

	// 竹の生成位置ずらし値
	static constexpr int CREATE_OFFSET_X = 48;

	enum class STATE
	{
		ANIMATION,
		GROWING,
		MAX
	};

	// 所有者
	EnemyPanda& owner_;

	// 所有者のパラメータ
	ParameterEnemyPanda& parameter_;

	// 状態
	STATE state_;

	// 攻撃位置
	Vector2F attackPos_;

	// 竹の生成位置
	Vector2F createBambooPos_;

	// 竹の生成回数
	int createBambooCount_;

	// 竹の生成インターバル
	float createIntervalTime_;

	// 攻撃コライダー
	std::shared_ptr<ColliderCircle> attackCollider_;

	// 更新処理
	std::function<void()> update_;

	// 状態遷移の管理マップ
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// 更新処理
	void UpdateAnimation();
	void UpdateGrowing();

	// 状態更新処理
	void ChangeState(const STATE state);
	void ChangeStateAnimation();
	void ChangeStateGrowing();

	// 竹生成処理
	void CreateBamboo();
};