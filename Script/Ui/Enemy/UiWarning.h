#pragma once
#include "../UiBase.h"

class EnemyBase;

class UiWarning : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiWarning(const EnemyBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiWarning() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	const EnemyBase& owner_;
	float deleteTimer_ = 0.0f;
};