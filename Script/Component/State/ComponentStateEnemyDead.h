#pragma once
#include "ComponentCharacterStateBase.h"

class EnemyBase;
class InputManager;

class ComponentStateEnemyDead : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner"></param>
	ComponentStateEnemyDead(EnemyBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateEnemyDead() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 所有者
	EnemyBase& owner_;
};