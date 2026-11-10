#pragma once
#include "EnemyBoss.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyAzagrim.h"

class EnemyAzagrim : public EnemyBoss
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter"></param>
	explicit EnemyAzagrim(std::unique_ptr<ParameterEnemyAzagrim> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyAzagrim() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEnemyAzagrim& GetParameter() { return *parameterEnemyAzagrim_; }

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name=""></param>
	void Update(void) override;

private:

	//固有のパラメータ
	ParameterEnemyAzagrim* parameterEnemyAzagrim_;
};

