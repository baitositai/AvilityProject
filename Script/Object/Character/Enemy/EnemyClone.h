#pragma once
#include "EnemyBase.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyClone.h"

class ParameterEnemyClone;

class EnemyClone : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit EnemyClone(std::unique_ptr<ParameterEnemyClone> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyClone() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEnemyClone& GetParameter() { return *parameterEnemy_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterEnemyClone& GetParameter() const { return *parameterEnemy_; }

private:

	// パラメータ情報
	ParameterEnemyClone* parameterEnemy_;
};