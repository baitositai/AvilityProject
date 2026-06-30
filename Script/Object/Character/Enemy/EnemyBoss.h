#pragma once
#include "EnemyBase.h"
class EnemyBoss : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	EnemyBoss(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyBoss() override;

private:

	/// <summary>
	/// UIの初期化
	/// </summary>
	virtual void InitUi() override;
};

