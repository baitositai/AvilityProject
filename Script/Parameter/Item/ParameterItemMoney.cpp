#include "ParameterItemMoney.h"

ParameterItemMoney::ParameterItemMoney():
	amount_(-1)
{
}

ParameterItemMoney::~ParameterItemMoney()
{
}

void ParameterItemMoney::LoadParameter(const Json& parameter)
{
	// 基底クラスの処理
	ParameterItem::LoadParameter(parameter);

	// 個別のパラメータ読み込み
	amount_ = parameter.value("amount", -1);
}
