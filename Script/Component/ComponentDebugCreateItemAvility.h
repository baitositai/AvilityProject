#pragma once
#include "ComponentBase.h"

class InputManager;

class ComponentDebugCreateItemAvility : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentDebugCreateItemAvility(ActorBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentDebugCreateItemAvility() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

private:

	// 入力管理クラス
	InputManager& inputManager_;

	// アビリティ種類
	int type_;
};

