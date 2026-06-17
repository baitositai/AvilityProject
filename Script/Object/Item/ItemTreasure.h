#pragma once
#include "ItemBase.h"
#include "../../Parameter/Item/ParameterItemTreasure.h"

class Player;

class ItemTreasure : public ItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit ItemTreasure(std::unique_ptr<ParameterItemTreasure> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemTreasure() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// リソース取得
	/// </summary>
	void InitResource() override;

	/// <summary>
	/// プレイヤーの追従
	/// </summary>
	/// <param name="player"></param>
	void FollowPlayer(Player& player);

	/// <summary>
	/// 追従解除
	/// </summary>
	void FollowRemove();

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterItemTreasure& GetParameter() { return *parameterItemTreasure_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterItemTreasure& GetParameter() const { return *parameterItemTreasure_; }

private:

	// お宝の保持番号
	int index_;

	// 所有者のポインタ
	const Player* owner_;

	// 所有者の頭位置
	Vector2F ownerHeadPos_;

	// パラメータ情報
	ParameterItemTreasure* parameterItemTreasure_;

	// 追従座標の更新
	void UpdateFollow();
};