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
	/// 投げる処理
	/// </summary>
	/// <param name="throwDir">投げられる方向</param>
	void Throw(const Vector2F& throwDir, const int attackPower);

	/// <summary>
	/// 追従解除
	/// </summary>
	void FollowRemove();

	/// <summary>
	/// 投げのリセット
	/// </summary>
	void ResetThrow();

	/// <summary>
	/// プレイヤーが投げた分位置番号を調整
	/// </summary>
	void OffsetIndex();

	/// <summary>
	/// 投げ判定を返す
	/// </summary>
	/// <returns>投げ判定</returns>
	const bool IsThrow() const { return isThrow_; }

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

	// 定数バッファサイズ
	static constexpr int CONST_BUFFER_SIZE = 2;
	
	// 所有者のポインタ
	const Player* owner_;

	// お宝の保持番号
	int index_;

	// 投げ判定
	bool isThrow_;

	// 重力方向のバックアップ
	ParameterActor::DIR preGravityDir_;

	// パラメータ情報
	ParameterItemTreasure* parameterItemTreasure_;

	// 追従座標の更新
	void UpdateFollow();

	// 描画初期化
	void InitDraw() override;

	// 着地処理
	void Landing() override;
};