#pragma once

class ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentBase();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() {};

private:
};

