#pragma once
#include "CharacterBase.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"

class ParameterPlayer;
class ComponentAvilityBase;
class ColliderBox;
enum class ABILITY_SLOT;

class Player : public CharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit Player(std::unique_ptr<ParameterPlayer> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

	/// <summary>
	/// 攻撃のリセット
	/// </summary>
	void AttackReset();

	/// <summary>
	/// 自身のコライダーのクローンを生成して返す
	/// </summary>
	/// <returns>自身のコライダーのクローン</returns>
	std::shared_ptr<ColliderBox> CreateColliderClone();

	/// <summary>
	/// アビリティコンポーネントの設定
	/// </summary>
	/// <param name="component">コンポーネント</param>
	void SetAbilityComponent(std::unique_ptr<ComponentAvilityBase> component);

	/// <summary>
	/// 各スロットのアビリティの活動状態を設定
	/// </summary>
	/// <param name="abilitySlot">アビリティスロット</param>
	/// <param name="isActive">活動状態</param>
	void SetAbilityActive(const ABILITY_SLOT abilitySlot, const bool isActive);

	/// <summary>
	/// アビリティコンポーネントを外す
	/// </summary>
	/// <param name="abilitySlot">アビリティスロット</param>
	void RemoveAbilityComponent(const ABILITY_SLOT abilitySlot);

	/// <summary>
	/// 指定したスロットのアビリティコンポーネントをリセットする
	/// </summary>
	/// <param name="abilitySlot">アビリティスロット</param>
	void ResetAbilityComponent(const ABILITY_SLOT abilitySlot);

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterPlayer& GetParameter() { return *parameterPlayer_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterPlayer& GetParameter() const { return *parameterPlayer_; }

private:

	// パラメータ情報
	ParameterPlayer* parameterPlayer_;

	// アビリティコンポーネントのマップ
	std::unordered_map<ABILITY_SLOT, std::unique_ptr<ComponentAvilityBase>> abilityComponents_;	

	// アビリティ更新処理
	void UpdateComponentAvility();
};