#pragma once
#include "UiPlayerBase.h"
class UiPlayerMessages : public UiPlayerBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiPlayerMessages(const Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiPlayerMessages() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Draw() override;

private:

	// スプライト画像
	int* handles_;
};