#pragma once
#include <unordered_map>
#include "ComponentBase.h"
#include "../Common/Vector2F.h"
#include "../../Object/ActorBase.h"

class ParameterActor;

class ComponentGravity : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentGravity(ActorBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentGravity() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	ParameterActor& parameter_;
};