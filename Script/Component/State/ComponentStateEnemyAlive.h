#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "ComponentCharacterStateBase.h"

class EnemyBase;
class ParameterEnemy;
class ColliderFan;
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
		PATROL,	// パトロール
		CHASE,	// 追跡
	};

	// 所有者
	EnemyBase& owner_;

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

	// 所有者のパラメータ
	ParameterEnemy& parameter_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 状態
	STATE state_;

	// 視野角用コライダー
	std::shared_ptr<ColliderFan> colliderFan_;

	// 状態別更新
	std::function<void()> update_;

	// 状態別処理のマップ
	std::unordered_map<STATE, std::function<void()>> stateChangeMap_;

	//移動種類別に更新処理
	void UpdatePatrolLand();
	void UpdatePatrolAir();
	void UpdateChase();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStatePatrol();
	void ChangeStateChase();

	// 視界角度の更新
	void UpdateEyeAngle();

	// アニメーションの更新
	void UpdateAnimation();
};