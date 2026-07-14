#pragma once
#include "../ParameterActor.h"
#include "../../Manager/Game/ItemTypes.h"

class ParameterItem : public ParameterActor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterItem() override;

	// 描画番号
	int spriteIndex_;

	// 値段
	int amount_;

	// ショップメッセージ
	std::string shopMessage_;

	// アイテムの種類
	ItemTypes::TYPE itemType_;
};