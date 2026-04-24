#pragma once
#include "ComponentBase.h"

class ActorBase;

class ComponentBlast :
    public ComponentBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentBlast(ActorBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentBlast() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
private:

	//爆発カウント
	float blastCnt_;
};

