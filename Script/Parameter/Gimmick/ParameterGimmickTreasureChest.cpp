#include "ParameterGimmickTreasureChest.h"

ParameterGimmickTreasureChest::ParameterGimmickTreasureChest()
{
}

ParameterGimmickTreasureChest::~ParameterGimmickTreasureChest()
{
}

void ParameterGimmickTreasureChest::LoadParameter(const Json& parameter)
{
	// 基底クラスの処理
	ParameterActor::LoadParameter(parameter);

	// アニメーションデータの取得
	LoadParameterAnimation(parameter);
}
