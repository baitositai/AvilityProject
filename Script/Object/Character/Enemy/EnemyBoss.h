#pragma once
#include "EnemyBase.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyBoss.h"

class EnemyBoss : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	EnemyBoss(std::unique_ptr<ParameterEnemyBoss> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyBoss() override;

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterEnemyBoss& GetParameter() const { return *parameterEnemyBoss_; }

protected:

	// 型変換用のパラメータを返す関数
	ParameterEnemyBoss* GetParameterEnemyBossPtr() { return parameterEnemyBoss_; }

private:

	// キャラクターのパラメータ
	ParameterEnemyBoss* parameterEnemyBoss_;

	// UIの初期化
	virtual void InitUi() override;
};

