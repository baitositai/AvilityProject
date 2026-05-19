#pragma once
#include "../CharacterBase.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyClone.h"

class ParameterEnemy;

class EnemyClone : public CharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="stateComponentNameList">状態別コンポーネントリスト</param>
	/// <param name="defaultComponentNameList">通常のコンポーネントリスト</param>
	/// <param name="animation">アニメーション</param>
	EnemyClone(
		std::unique_ptr<ParameterEnemyClone> parameter = nullptr,
		std::unique_ptr<Animation> animation = nullptr);

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

private:

	// パラメータ情報
	Parameter parameter_;

};

