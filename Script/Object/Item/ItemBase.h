#pragma once
#include "../ActorBase.h"
#include "../../Parameter/Item/ParameterItem.h"

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
	/// デバッグ描画
	/// </summary>
	virtual void DebugDraw() override;

protected:

	// 型変換用のパラメータを返す関数
	ParameterItem* GetParameterCharacterPtr() { return parameterItem_; }

	// アイテムのパラメータ
	ParameterItem* parameterItem_;
};