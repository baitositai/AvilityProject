#pragma once
#include "GimmickBase.h"
class GimmickDoor : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	GimmickDoor(std::unique_ptr<ParameterGimmick> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickDoor() override;

private:

	// パラメータ情報
	ParameterGimmick* parameterDoor_;
};