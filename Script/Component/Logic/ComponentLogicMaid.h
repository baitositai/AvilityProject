#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "ComponentLogicBase.h"
#include "../../Common/Vector2F.h"
#include "../../Parameter/ParameterActor.h"

class EnemyMaid;
class ParameterEnemyMaid;
class ColliderFan;
class ColliderCircle;
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

	// 重力を切り替える時間
	static constexpr float CHANGE_GRAVITY_TIME = 3.0f;

	// 停止時間
	static constexpr float STOP_TIME = 0.4f;

	// 追加重力量
	static constexpr float ADD_GRAVITY = 16.0f;

	// 攻撃回数
	static constexpr int SPECIAL_ATTACK_COUNT = 30;

	// 特別攻撃遅延時間
	static constexpr float SPECIAL_ATTACK_DELAY_TIME = 0.8f;

	// テレポート時間
	static constexpr float TEREPORT_TIME = 0.5f;

	//カメラシェイク関連
	static constexpr float CAMERA_SHAKE_TIME = 0.3f;	//シェイク時間
	static constexpr float CAMERA_SHAKE_POWER = 3.0f;	//シェイク力

	enum class STATE
	{
		COLLECT,	// 集める
		JUMP,		// ジャンプ
		STAMP_READY,// スタンプ準備
		STAMP,		// スタンプ
		SPECIAL,	// スペシャル
		TEREPORT,	// テレポート	
		DELAY,		// 遅延
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

	// タイマー
	float timer_;

	// 特別攻撃判定
	bool isSpecialAttack_;

	// 特別攻撃の開始フレーム
	int specialAttackStartFrame_;

	// 特別攻撃の回数
	int specialAttackCount_;

	// 特別攻撃位置
	Vector2F specialAttackPos_;

	// 状態
	STATE state_;

	// 重力変更先
	ParameterActor::DIR nextGravityDir_;

	// 状態別更新
	std::function<void()> update_;

	// 特別攻撃用コライダー
	std::shared_ptr<ColliderCircle> colliderCircle_;

	// 視野角用コライダー
	std::shared_ptr<ColliderFan> colliderFan_;

	// 食べ物を落とす処理
	std::unique_ptr<FoodShawer> foodShawer_;

	// 状態別処理のマップ
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	//移動種類別に更新処理
	void UpdateCollect();
	void UpdateJump();
	void UpdateStampReady();
	void UpdateStamp();
	void UpdateSpecial();
	void UpdateTeleport();
	void UpdateDelay();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateCollect();
	void ChangeStateJump();
	void ChangeStateStampReady();
	void ChangeStateStamp();
	void ChangeStateSpecial();
	void ChangeStateTeleport();
	void ChangeStateDelay();

	// 視界角度の更新
	void UpdateEyeAngle();

	// アニメーションの更新
	void UpdateAnimation();

	// 攻撃
	void Attack();

	// エアースラッシュ
	void CreateAirSlash(const Vector2F& dir);

};