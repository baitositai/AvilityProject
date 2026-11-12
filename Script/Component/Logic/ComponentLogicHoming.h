#pragma once
#include "ComponentLogicBase.h"

class EnemyAzagrim;

class ComponentLogicHoming : public ComponentLogicBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentLogicHoming(EnemyAzagrim& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentLogicHoming() override;

	/// <summary>
	/// 生成処理
	/// </summary>
	void Create() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	EnemyAzagrim& owner_;

};

