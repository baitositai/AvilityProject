#pragma once
#include "EnemyBoss.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyMaid.h"

class EnemyMaid : public EnemyBoss
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyMaid(std::unique_ptr<ParameterEnemyMaid> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyMaid() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEnemyMaid& GetParameter() { return *parameterEnemyMaid_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterEnemyMaid& GetParameter() const { return *parameterEnemyMaid_; }

private:

	// パラメータ情報
	ParameterEnemyMaid* parameterEnemyMaid_;
};