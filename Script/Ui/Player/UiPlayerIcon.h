#pragma once
#include "UiPlayerBase.h"

class Player;

class UiPlayerIcon : public UiPlayerBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiPlayerIcon(const Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiPlayerIcon() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
};

