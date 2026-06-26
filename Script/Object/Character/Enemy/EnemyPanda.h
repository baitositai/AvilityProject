#pragma once
#include "EnemyBase.h"
#include "../../../Parameter/Character/Enemy/ParameterEnemyPanda.h"

class EnemyPanda : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyPanda(std::unique_ptr<ParameterEnemyPanda> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyPanda() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEnemyPanda& GetParameter() { return *parameterEnemyPanda_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterEnemyPanda& GetParameter() const { return *parameterEnemyPanda_; }

private:

	// パラメータ情報
	ParameterEnemyPanda* parameterEnemyPanda_;
};

