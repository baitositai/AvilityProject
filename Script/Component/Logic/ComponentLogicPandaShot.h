#pragma once
#include <random>
#include "ComponentLogicBase.h"

class EnemyPanda;
class ColliderBox;

class ComponentLogicPandaShot : public ComponentLogicBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentLogicPandaShot(EnemyPanda& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentLogicPandaShot() override;

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
		START,
		READY,
		CHARGE,
		SHOT,
		MAX
	};

	// 竹の生成数
	static constexpr int CREATE_BAMBOO_COUNT = 5;

	//カメラシェイク関連
	static constexpr float CAMERA_SHAKE_TIME = 0.3f;	//シェイク時間
	static constexpr float CAMERA_SHAKE_POWER =3.0f;	//シェイク力

	// 所有者
	EnemyPanda& owner_;

	// 所有者のパラメータ
	ParameterEnemyPanda& parameter_;

	// 反射回数
	int reflectCount_;

	// 移動位置
	Vector2F moveStartPos_;
	Vector2F moveEndPos_;

	// 移動方向
	Vector2F moveDir_;

	// タイマー
	float timer_;

	// 状態
	STATE state_;

	// 更新処理
	std::function<void()> update_;

	// 状態遷移の管理マップ
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// 攻撃コライダー
	std::shared_ptr<ColliderBox> attackCollider_;

	// 乱数生成エンジン
	std::mt19937 randomCountEngine_;

	// エフェクト番号
	int effectId_;

	// 更新処理
	void UpdateStart();
	void UpdateReady();
	void UpdateCharge();
	void UpdateShot();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateStart();
	void ChangeStateReady();
	void ChangeStateCharge();
	void ChangeStateShot();

	// 衝突判定と押し出し処理の共通ロジック
	void ProcessCollision(bool isXAxis);

	// 接地判定の共通ロジック
	void CheckGroundStatus(float moveVal, bool isXAxis);

	// 飛び回った後の処理
	void ShotEnd();

	// 竹の生成
	void CreateBamboo();
};