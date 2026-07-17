#pragma once
#include "../ActorBase.h"
#include "../../Parameter/Item/ParameterItem.h"
#include "../../Manager/Game/CollisionTags.h"

class ItemBase : public ActorBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit ItemBase(std::unique_ptr<ParameterItem> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ItemBase() override;

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
	/// 持ち越し判定
	/// </summary>
	/// <returns>trueの場合持ち越しする</returns>
	const bool IsCarryOver() const;

	/// <summary>
	/// 持ち越し設定
	/// </summary>
	/// <param name="isCarry">持ち越し判定</param>
	void SetIsCarryOver(const bool isCarry);

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterItem& GetParameter() { return *parameterItem_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterItem& GetParameter() const { return *parameterItem_; }

protected:	
	
	// 削除時間
	static constexpr float DELETE_TIME = 30.0f;	

	// 点滅開始時間
	static constexpr float BLINK_START_TIME = 5.0f;
	
	// アイテムのパラメータ
	ParameterItem* parameterItem_;

	// 削除用タイマー
	float deleteTimer_;

	// 持ち越し判定
	bool isCarryOver_;

	// 衝突判定用タグ
	CollisionTags::TAG tag_;

	// 型変換用のパラメータを返す関数
	ParameterItem* GetParameterItemPtr() { return parameterItem_; }

	// 削除タイマーのカウント
	void CountDeleteTime();
};