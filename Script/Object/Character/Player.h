#pragma once
#include "CharacterBase.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "../../Component/Avility/AvilityTypes.h"

class ParameterPlayer;
class ComponentAvilityBase;
class ItemTreasure;
class PlayerManager;
class ColliderBox;
class UiSpeechBubbleBase;

class Player : public CharacterBase
{
public:

	// 持てるアビリティの上限
	static constexpr int AVILITY_MAX = 3;

	// アビリティ選択時間
	static constexpr float AVILITY_SELECT_TIME = 3.0f;

	// 退出用入力時間
	static constexpr float LEAVE_INPUT_TIME = 3.0f;

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
	/// 初期化処理
	/// </summary>
	void Init() override;

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
	void Damage(const int damage, const Vector2& hitPos = {}) override;

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
	/// アイテムを投げる処理
	/// </summary>
	/// <param name="throwDir">投げる方向</param>
	void ThrowItem(const Vector2F& throwDir);

	/// <summary>
	/// アイテムのアタッチ
	/// </summary>
	/// <param name="item">アイテム</param>
	void AttachedItem(ItemTreasure* item);

	/// <summary>
	/// 攻撃力の上昇
	/// </summary>
	/// <param name="attackPower">攻撃力加算量</param>
	void AttackPowerUp(const int addAttackPower);

	/// <summary>
	/// 最大体力を上昇
	/// </summary>
	/// <param name="addHpMax">最大体力加算量</param>
	void HpMaxUp(const int addHpMax);

	/// <summary>
	/// 速度を上昇
	/// </summary>
	/// <param name="addSpeed">スピード加算量</param>
	void SpeedUp(const float addSpeed);

	/// <summary>
	/// アイテムのデタッチ
	/// </summary>
	void DetachItem();

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
	const Vector2F GetHeadLocalPos(const int index) const;

	/// <summary>
	/// 盗んだお金の総額を返す
	/// </summary>
	/// <returns>お金の総額</returns>
	const int GetTotalLootTreasuresMoney() const;

	/// <summary>
	/// アビリティリソース番号を返す
	/// </summary>
	/// <returns>アビリティリソース番号</returns>
	const std::vector<int>& GetAvilityItemResourceIndexs() const { return avilityItemResourceIndexs_; }

	// マテリアルの設定
	void SetMaterialBuf(const int index, FLOAT4 buf);

	// アウトラインカラーの取得
	VECTOR GetOutlineColor() const;

private:

	// アウトラインの色
	static constexpr VECTOR PLATYER1_COLOR = { 0.0f, 0.0f, 1.0f };
	static constexpr VECTOR PLATYER2_COLOR = { 1.0f, 0.0f, 0.0f };
	static constexpr VECTOR PLATYER3_COLOR = { 0.0f, 1.0f, 0.0f };
	static constexpr VECTOR PLATYER4_COLOR = { 1.0f, 1.0f, 0.0f };
	std::vector<VECTOR> PLAYER_OUTLINE_COLORS;

	// 定数バッファ―サイズ
	static constexpr int PLAYER_CONST_BUFFER_SIZE = 4;

	// 退出用入力時間
	float leaveInputTime_;

	// アビリティリソース番号を格納
	std::vector<int> avilityItemResourceIndexs_;

	// 保持しているお宝
	std::vector<ItemTreasure*> attachedTreasures_;

	// パラメータ情報
	ParameterPlayer* parameterPlayer_;

	// 吹き出し
	UiSpeechBubbleBase* speechBubble_;

	// プレイヤー管理クラス
	PlayerManager& playerManager_;

	// アビリティコンポーネント
	std::vector<std::unique_ptr<ComponentAvilityBase>> avilityComponents_;	

	// 選択用で保持する予備
	std::unique_ptr<ComponentAvilityBase> spareAvilityComponent_;

	// 描画関係の初期化
	void InitDraw() override;

	// UIの初期化
	void InitUi() override;

	// アビリティの生成
	void CreateAvilities();

	// アビリティ更新処理
	void UpdateComponentAvility();

	// アビリティの選択
	void SelectAvility();

	// 途中退出用処理
	void GameLeave();

	// 更新後処理
	void UpdateAfter();

	// アビリティリソース番号の設定
	void SetAvilityResourceIndexs();

	// アビリティ取得エフェクトの生成
	void CreateEffectGetAbility();
};
