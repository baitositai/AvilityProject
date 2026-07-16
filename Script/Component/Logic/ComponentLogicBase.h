#pragma once
#include "../ComponentBase.h"

class EnemyBase;
class SceneManager;
class CollisionManager;
class GimmickManager;
class ItemManager;
class PlayerManager;
class SpriteEffectManager;
class SoundManager;

class ComponentLogicBase : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentLogicBase(EnemyBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentLogicBase() override;

	/// <summary>
	/// 生成
	/// </summary>
	virtual void Create() override;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 取り外し処理
	/// </summary>
	virtual void Remove() override;

	/// <summary>
	/// 攻撃判定をリセット
	/// </summary>
	virtual void AttackReset();

	/// <summary>
	/// ロジックの終了を返す
	/// </summary>
	/// <returns>終了判定</returns>
	const bool IsEnd() const { return isEnd_; }

	/// <summary>
	/// 実行確立を設定
	/// </summary>
	/// <param name="probability">実行確立</param>
	void SetProbability(const float probability) { probability_ = probability; }

	/// <summary>
	/// 実行確立を返す
	/// </summary>
	/// <returns>実行確立</returns>
	virtual const float GetProbability() const { return probability_; }

protected:

	// 終了判定
	bool isEnd_;

	// 実行確率
	float probability_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 衝突判定管理クラス
	CollisionManager& collisionManager_;

	// アイテム管理クラス
	ItemManager& itemManager_;

	// ギミック管理クラス
	GimmickManager& gimmickManager_;

	// プレイヤー管理クラス
	PlayerManager& playerManager_;

	// エフェクト管理クラス
	SpriteEffectManager& spriteEffectManager_;

	// サウンド管理クラス
	SoundManager& soundManager_;
};