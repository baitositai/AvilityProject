#pragma once
#include "ComponentAvilityBase.h"

class ComponentAvilityGiant : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentAvilityGiant(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityGiant() override;

	/// <summary>
	/// 生成処理
	/// </summary>
	void Create() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 取り外し時の処理
	/// </summary>
	void Remove() override;

private:

	// 拡大率
	static constexpr float SCALE = 2.0f;

	// 重力制御処理
	void ProcessGravity();

};

