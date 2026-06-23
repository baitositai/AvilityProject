#pragma once
#include "UiSpeechBubbleBase.h"

class Player;

class UiSpeechBubbleSelectAvility : public UiSpeechBubbleBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiSpeechBubbleSelectAvility(const Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiSpeechBubbleSelectAvility() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 所有者
	const Player& owner_;
};

