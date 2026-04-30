#pragma once

class ActorBase;

class ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentBase(ActorBase* owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentBase();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

protected:

	ActorBase* owner_;
};

