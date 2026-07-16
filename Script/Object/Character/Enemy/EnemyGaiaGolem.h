#pragma once
#include "EnemyBoss.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyGaiaGolem.h"

class EnemyGaiaGolem :
    public EnemyBoss
{
public:

    /// <summary>
	/// コンストラクタ
    /// </summary>
    /// <param name="parameter"></param>
    explicit EnemyGaiaGolem(std::unique_ptr<ParameterEnemyGaiaGolem> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyGaiaGolem() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEnemyGaiaGolem& GetParameter() { return *parameterEnemyGaiaGolem_; }
	
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name=""></param>
	void Update(void) override;
private:

	//固有のパラメータ
	ParameterEnemyGaiaGolem* parameterEnemyGaiaGolem_;
};

