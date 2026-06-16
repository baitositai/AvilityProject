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
	/// 描画処理
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	virtual void DebugDraw() override;

protected:

	// 衝突判定用タグ
	CollisionTags::TAG tag_;

	// 型変換用のパラメータを返す関数
	ParameterItem* GetParameterItemPtr() { return parameterItem_; }

	// アイテムのパラメータ
	ParameterItem* parameterItem_;
};