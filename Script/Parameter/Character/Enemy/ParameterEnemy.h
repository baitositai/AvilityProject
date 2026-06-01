#pragma once
#include "../ParameterCharacter.h"

class ParameterEnemy : public ParameterCharacter
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEnemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterEnemy() override;

    /// <summary>
	/// 外部データの読み込み
	/// </summary>
	/// <param name="parameter">読み込むJSONデータ</param>
    virtual void LoadParameter(const Json& parameter) override;

private:

};

