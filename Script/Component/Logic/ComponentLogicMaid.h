#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "ComponentLogicBase.h"
#include "../../Common/Vector2F.h"

class EnemyMaid;
class ParameterEnemyMaid;
class ColliderFan;
class FoodShawer;

class ComponentLogicMaid : public ComponentLogicBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentLogicMaid(EnemyMaid& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentLogicMaid() override;

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

	// 所有者
	EnemyMaid& owner_;

	// パラメータ
	ParameterEnemyMaid& parameter_;

	enum class STATE
	{
		COLLECT,	// 集める
	};

	// 視界用角度
	float eyeBaseAngle_;

	// 移動停止時間
	float stopTimer_;

	// パトロールの移動距離
	Vector2F moveDistance_;

	// 移動方向
	float moveDirection_;

	// 移動判定
	bool isMove_;

	// 状態
	STATE state_;

	// 状態別更新
	std::function<void()> update_;

	// 視野角用コライダー
	std::shared_ptr<ColliderFan> colliderFan_;

	// 食べ物を落とす処理
	std::unique_ptr<FoodShawer> foodShawer_;

	// 状態別処理のマップ
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	//移動種類別に更新処理
	void UpdateCollect();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateCollect();

	// 視界角度の更新
	void UpdateEyeAngle();
};