#pragma once
#include "../CharacterBase.h"
#include "../../../Parameter/Character/Enemy/ParameterEnemy.h"

class ParameterEnemy;

class EnemyBase : public CharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyBase(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBase() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEnemy& GetParameter() { return *parameterEnemy_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterEnemy& GetParameter() const { return *parameterEnemy_; }

protected:

	// 型変換用のパラメータを返す関数
	ParameterEnemy* GetParameterEnemyPtr() { return parameterEnemy_; }

private:

	// キャラクターのパラメータ
	ParameterEnemy* parameterEnemy_;
};

