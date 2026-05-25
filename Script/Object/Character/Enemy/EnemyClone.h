#pragma once
#include "../CharacterBase.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyClone.h"

class ParameterEnemyClone;

class EnemyClone : public CharacterBase
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
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

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