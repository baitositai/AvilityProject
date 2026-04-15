#pragma once
#include "ComponentBase.h"

class ComponentMove : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentMove(ActorBase& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentMove() override;
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

};

