#pragma once
#include <functional>
#include <unordered_map>
#include "../ActorBase.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"

class ComponentBase;

class CharacterBase : public ActorBase
{
public:
	
	// キャラクターの共通パラメータ
	struct Parameter : public ActorBase::Parameter
	{
		int hp = -1;						// 体力
		int attackPower = -1;				// 攻撃力
		bool isGround = false;				// 地面判定
		bool isFall = false;				// 落下判定
		float invincibleTimeMax = 0.0f;		// 最大無敵時間
		float invincibleTime = 0.0f;			// 無敵時間
		float jumpPow = 0.0f;				// ジャンプ力
		float jumpPowMax = 0.0f;			// ジャンプ力の最大量
		Vector2 hitBoxSize = {};			// 衝突判定用ボックスサイズ
		Vector2F knockBackPower = {};		// ノックバックパワー
		float knockBackDistance_;			// ノックバック距離
	};

	// キャラクター共通の状態
	enum class STATE
	{
		RESPAWN,	// 復活
		ALIVE,		// 生存
		ATTACK,		// 攻撃
		HIT,		// ヒット
		DEAD,		// 死亡
		MAX
	};
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="stateComponentNameList">状態別コンポーネント生成リスト</param>
	/// <param name="defaultComponentNameList">通常コンポーネント生成リスト</param>
	/// <param name="animation">アニメーション</param>
	CharacterBase(
		Parameter* parameter, 
		const std::unordered_map<std::string, std::string> stateComponentNameList,
		const std::vector<std::string> defaultComponentNameList = {}, 
		std::unique_ptr<Animation> animation = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CharacterBase() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	virtual void DebugDraw() override;

	/// <summary>
	/// 状態遷移処理
	/// </summary>
	/// <param name="state">状態</param>
	void ChangeState(const STATE state);

	/// <summary>
	/// ダメージ設定
	/// </summary>
	/// <param name="damage">ダメージ</param>
	void Damage(const int damage);

	/// <summary>
	/// 地面判定の設定
	/// </summary>
	/// <param name="isGround">地面判定</param>
	void SetIsGround(const bool isGround) { characterParameterPtr_->isGround = isGround; }

	/// <summary>
	/// 落下判定の設定
	/// </summary>
	/// <param name="isFall">落下判定</param>
	void SetIsFall(const bool isFall) { characterParameterPtr_->isGround = isFall; }

	/// <summary>
	/// 無敵判定
	/// </summary>
	/// <param name="isInvicible">無敵判定</param>
	void SetIsInvincibleTime(const float invicibleTime) { characterParameterPtr_->invincibleTime = invicibleTime; }

	/// <summary>
	/// ジャンプ力を設定
	/// </summary>
	/// <param name="jumpPowMax">ジャンプ力</param>
	void SetJumpPow(const float jumpPow);

	/// <summary>
	/// 最大ジャンプ力を設定
	/// </summary>
	/// <param name="jumpPowMax">最大ジャンプ力</param>
	void SetJumpPowMax(const float jumpPowMax) { characterParameterPtr_->jumpPowMax = jumpPowMax; }

	/// <summary>
	/// ノックバックパワーの設定
	/// </summary>
	/// <param name="knockBackPower">ノックバックパワー</param>
	void SetKnockBackPower(const Vector2F& knockBackPower) { characterParameterPtr_->knockBackPower = knockBackPower; }

	/// <summary>
	/// 衝突する範囲を返す
	/// </summary>
	/// <returns>衝突する範囲</returns>
	const Vector2& GetHitBoxSize() const { return characterParameterPtr_->hitBoxSize; }

	/// <summary>
	/// 攻撃力を返す
	/// </summary>
	/// <returns>攻撃力</returns>
	const int GetAttackPower() const;

	/// <summary>
	/// 最大ジャンプ力を返す
	/// </summary>
	/// <returns>ジャンプ力</returns>
	const float GetJumpPow() const { return characterParameterPtr_->jumpPow; }

	/// <summary>
	/// 最大ジャンプ力を返す
	/// </summary>
	/// <returns>最大ジャンプ力</returns>
	const float GetJumpPowMax() const { return characterParameterPtr_->jumpPowMax; }

	/// <summary>
	/// 無敵時間を返す
	/// </summary>
	/// <returns>無敵時間</returns>
	const float GetInvincibleTime() const { return characterParameterPtr_->invincibleTime; }

	/// <summary>
	/// 地面判定を返す
	/// </summary>
	/// <returns>地面判定</returns>
	const bool IsGround() const { return characterParameterPtr_->isGround; }

	/// <summary>
	/// 落下判定を返す
	/// </summary>
	/// <returns>落下判定</returns>
	const bool IsFall() const { return characterParameterPtr_->isFall; }
	
	/// <summary>
	/// 無敵判定を返す
	/// </summary>
	/// <returns>無敵判定</returns>
	const bool IsInvincible() const { return characterParameterPtr_->invincibleTime > 0.0f; }

	/// <summary>
	/// ノックバックパワーを返す
	/// </summary>
	/// <returns></returns>
	const Vector2F& GeKnockBackPower() const { return characterParameterPtr_->knockBackPower; }

protected:	
	
	// キャラクターの状態
	STATE state_;	
	
	// 状態別更新処理を管理するコンポーネントマップ
	std::unordered_map<STATE, std::unique_ptr<ComponentBase>> componentStateMap_;

private:	

	// 状態をストリングで取得できる用
	const std::unordered_map<std::string, STATE> NAME_TO_STATE_MAP =
	{
		{ "alive", STATE::ALIVE },
		{ "dead", STATE::DEAD },
		{ "attack", STATE::ATTACK },
		{ "hit", STATE::HIT },
		{ "respawn", STATE::RESPAWN },
	};	
	
	// 生成するコンポーネントのマップ
	const std::unordered_map<std::string, std::string> STATE_COMPONENT_CREATE_MAP;
	
	// キャラクターのパラメータ
	Parameter* characterParameterPtr_;	

	// 状態遷移管理マップ
	std::unordered_map<STATE, std::function<void()>> stateChangeMap_;

	// コンポーネントの生成処理
	void CreateComponents() override;
};

