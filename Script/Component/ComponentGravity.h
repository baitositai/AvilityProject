#pragma once
#include <unordered_map>
#include "ComponentBase.h"
#include "../Common/Vector2F.h"
#include "../../Object/ActorBase.h"

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

	// 重力方向値の管理マップ
	const std::unordered_map<ActorBase::DIR, Vector2F> GRAVITY_DIR_MAP =
	{
		{ActorBase::DIR::RIGHT, Vector2F{1.0, 0.0}},
		{ActorBase::DIR::LEFT,Vector2F{-1.0, 0.0}},
		{ActorBase::DIR::UP,Vector2F{0.0, -1.0}},
		{ActorBase::DIR::DOWN,Vector2F{0.0, 1.0}}
	};

};

