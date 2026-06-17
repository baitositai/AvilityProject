#pragma once
#include "CharacterBase.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "../../Component/Avility/AvilityTypes.h"

class ParameterPlayer;
class ComponentAvilityBase;
class ItemTreasure;
class PlayerManager;
class ColliderBox;

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
	/// 削除処理
	/// </summary>
	void Delete() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

	/// <summary>
	/// 死亡処理
	/// </summary>	
	void Dead() override;

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">ダメージ</param>
	void Damage(const int damage) override;

	/// <summary>
	/// 準備処理
	/// </summary>
	void Ready();

	/// <summary>
	/// 誕生処理
	/// </summary>
	void Spawn();

	/// <summary>
	/// 攻撃後の処理
	/// </summary>
	void AttackAfter() override;

	/// <summary>
	/// 回復
	/// </summary>
	/// <param name="healHp">体力の回復量</param>
	void Heal(const int healHp);

	/// <summary>
	/// 自身のコライダーのクローンを生成して返す
	/// </summary>
	/// <returns>自身のコライダーのクローン</returns>
	std::shared_ptr<ColliderBox> CreateColliderClone();

	/// <summary>
	/// アイテムのアタッチ
	/// </summary>
	/// <param name="item">アイテム</param>
	void SetAttachedItem(ItemTreasure* item);

	/// <summary>
	/// アビリティコンポーネントの設定
	/// </summary>
	/// <param name="component">コンポーネント</param>
	void SetAvilityComponent(std::unique_ptr<ComponentAvilityBase> component);

	/// <summary>
	/// 各スロットのアビリティの活動状態を設定
	/// </summary>
	/// <param name="avilityType">アビリティ種類</param>
	/// <param name="isActive">活動状態</param>
	void SetAvilityActive(const AvilityTypes::TYPE avilityType, const bool isActive);

	/// <summary>
	/// 全てのアビリティの活動状態を設定
	/// </summary>
	/// <param name="isActive">活動状態</param>
	void SetAllAvilityComponentActive(const bool isActive);

	/// <summary>
	/// アビリティコンポーネントを外す
	/// </summary>
	/// <param name="avilityType">アビリティ種類</param>
	void RemoveAvilityComponent(const AvilityTypes::TYPE avilityType);

	/// <summary>
	/// アビリティコンポーネントをリセットする
	/// </summary>
	/// <param name="avilityType">アビリティ種類</param>
	void ResetAvilityComponent(const AvilityTypes::TYPE avilityType);

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

	/// <summary>
	/// 頭部の位置を返す
	/// </summary>
	/// <returns>頭部位置</returns>
	const Vector2F GetHeadPos(const int index) const;

private:

	// 持てるアビリティの上限
	static constexpr int AVILITY_MAX = 3;	
	
	// アビリティ選択時間
	static constexpr float AVILITY_SELECT_TIME = 2.5f;

	// 退出用入力時間
	static constexpr float LEAVE_INPUT_TIME = 3.0f;

	// 退出用入力時間
	float leaveInputTime_;

	// 選択時間
	float selectAvilityTime_;

	// 保持しているお宝
	std::vector<ItemTreasure*> attachedTreasures_;

	// パラメータ情報
	ParameterPlayer* parameterPlayer_;

	// プレイヤー管理クラス
	PlayerManager& playerManager_;

	// アビリティコンポーネント
	std::vector<std::unique_ptr<ComponentAvilityBase>> avilityComponents_;	

	// 選択用で保持する予備
	std::unique_ptr<ComponentAvilityBase> spareAvilityComponent_;

	// アビリティ更新処理
	void UpdateComponentAvility();

	// アビリティの選択
	void SelectAvility();

	// 途中退出用処理
	void GameLeave();

	// 更新後処理
	void UpdateAfter();
};