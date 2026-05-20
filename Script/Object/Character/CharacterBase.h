#pragma once
#include <functional>
#include <unordered_map>
#include "../ActorBase.h"
#include "../../Parameter/Character/ParameterCharacter.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"

class ParameterCharacter;

class CharacterBase : public ActorBase
{
public:

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
	explicit CharacterBase(std::unique_ptr<ParameterCharacter> parameter = nullptr);

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
	/// ジャンプ力を設定
	/// </summary>
	/// <param name="jumpPowMax">ジャンプ力</param>
	void SetJumpPow(const float jumpPow);

	/// <summary>
	/// パフを重ねた攻撃力を返す
	/// </summary>
	/// <returns>攻撃力</returns>
	const int GetAttackPowerWithBoost() const;
	
	/// <summary>
	/// 無敵判定を返す
	/// </summary>
	/// <returns>無敵判定</returns>
	const bool IsInvincible() const;
	
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
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterCharacter& GetParameter() { return *parameterCharacter_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterCharacter& GetParameter() const { return *parameterCharacter_; }

protected:		
	
	// 種類
	TYPE type_;

	// キャラクターの状態
	STATE state_;	
	
	// 状態別更新処理を管理するコンポーネントマップ
	std::unordered_map<STATE, std::unique_ptr<ComponentBase>> componentStateMap_;
	
	// 状態別コンポーネント処理の更新
	void UpdateComponentState();

	// 型変換用のパラメータを返す関数
	ParameterCharacter* GetParameterCharacterPtr() { return parameterCharacter_; }

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

	// 状態遷移管理マップ
	std::unordered_map<STATE, std::function<void()>> stateChangeMap_;

	// コンポーネントの生成処理
	void CreateComponents() override;	
	
	// キャラクターのパラメータ
	ParameterCharacter* parameterCharacter_;
};