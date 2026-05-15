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
		int jumpCount = -1;					// ジャンプ回数
		int jumpCountMax = -1;				// 最大ジャンプ回数
		float attackBoostRate_ = 0.0f;		// 攻撃力上昇率
		float invincibleTimeMax = 0.0f;		// 最大無敵時間
		float invincibleTime = 0.0f;		// 無敵時間
		float jumpPow = 0.0f;				// ジャンプ力
		float jumpPowMax = 0.0f;			// ジャンプ力の最大量
		Vector2F knockBackPower = {};		// ノックバックパワー
		float knockBackDistance_;			// ノックバック距離
		Vector2F defaultAttackLocalPos = {};// 通常攻撃の当たり判定調整座標	
		float defaultAttackRadius = 0.0f;	// 通常攻撃の範囲半径
	};

	// 種類
	enum class TYPE
	{
		PLAYER,								// プレイヤー
		ENEMY_CLONE,						// 敵:クローン
		MAX
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
	/// 着地処理
	/// </summary>
	void Landing() override;

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
	/// 状態別コンポーネントの活動状態を設定
	/// </summary>
	/// <param name="state">状態</param>
	/// <param name="isActive">活動状態</param>
	void SetStateComponentActive(const STATE state, const bool isActive);

	/// <summary>
	/// 無敵時間の設定
	/// </summary>
	/// <param name="invincibleTime">無敵時間</param>
	void SetIsInvincibleTime(const float invicibleTime) { characterParameterPtr_->invincibleTime = invicibleTime; }

	/// <summary>
	/// 無敵時間の追加
	/// </summary>
	/// <param name="addInvincibleTime">追加する無敵時間</param>
	void AddInvincibleTime(const float addInvincibleTime) { characterParameterPtr_->invincibleTime += addInvincibleTime; }

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
	/// ジャンプ回数の追加
	/// </summary>
	/// <param name="addJumpCount">ジャンプ回数</param>
	void AddJumpCount(const int addJumpCount) { characterParameterPtr_->jumpCount += addJumpCount; }

	/// <summary>
	/// ノックバックパワーの設定
	/// </summary>
	/// <param name="knockBackPower">ノックバックパワー</param>
	void SetKnockBackPower(const Vector2F& knockBackPower) { characterParameterPtr_->knockBackPower = knockBackPower; }

	/// <summary>
	/// 攻撃力の追加
	/// </summary>
	/// <param name="addAttackPower">追加する攻撃力</param>
	void AddAttackPower(const int addAttackPower) const { characterParameterPtr_->attackPower += addAttackPower; }

	/// <summary>
	/// 攻撃力上昇率の追加
	/// </summary>
	/// <param name="addAttackBoostRate">追加する攻撃力上昇率</param>
	void AddAttackBoostRate(const float addAttackBoostRate) const { characterParameterPtr_->attackBoostRate_ += addAttackBoostRate; }

	/// <summary>
	/// 攻撃力を返す
	/// </summary>
	/// <returns>攻撃力</returns>
	const int GetAttackPower() const { return characterParameterPtr_->attackPower; }

	/// <summary>
	/// パフを重ねた攻撃力を返す
	/// </summary>
	/// <returns>攻撃力</returns>
	const int GetAttackPowerWithBoost() const;

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
	/// ジャンプ回数を返す
	/// </summary>
	/// <returns>ジャンプ回数</returns>
	const int GetJumpCount() const { return characterParameterPtr_->jumpCount; }

	/// <summary>
	/// 無敵時間を返す
	/// </summary>
	/// <returns>無敵時間</returns>
	const float GetInvincibleTime() const { return characterParameterPtr_->invincibleTime; }
	
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
	
	/// <summary>
	/// 種類を返す
	/// </summary>
	/// <returns>種類</returns>
	const TYPE GetType() const { return type_; }

	/// <summary>
	/// 状態を返す
	/// </summary>
	/// <returns>状態</returns>
	const STATE GetState() const { return state_; }

	/// <summary>
	/// 状態別コンポーネントの活動状態を返す
	/// </summary>
	/// <param name="state">状態</param>
	/// <returns>活動状態</returns>
	bool IsStateComponentActive(const STATE state) const;

	/// <summary>
	/// 通常攻撃の位置を調整する座標を返す
	/// </summary>
	/// <returns>通常攻撃の相対座標</returns>
	const Vector2F GetDefaultAttackLocalPos() const { return characterParameterPtr_->defaultAttackLocalPos; }

	/// <summary>
	/// 通常攻撃の範囲半径を返す
	/// </summary>
	/// <returns>通常攻撃の範囲半径</returns>
	const float GetDefaultAttackRadius() const { return characterParameterPtr_->defaultAttackRadius; }

protected:	
	
	// 種類
	TYPE type_;

	// キャラクターの状態
	STATE state_;	
	
	// 状態別更新処理を管理するコンポーネントマップ
	std::unordered_map<STATE, std::unique_ptr<ComponentBase>> componentStateMap_;

	// 状態別コンポーネント処理の更新
	void UpdateComponentState();

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

