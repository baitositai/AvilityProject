#pragma once
#include <memory>
#include "UiGameBase.h"

class UiTimer;
class PlayerCheckAnnihilation;

class UiPlayerAnnhilation : public UiGameBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiPlayerAnnhilation(const PlayerCheckAnnihilation& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiPlayerAnnhilation() override;
	
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	// 所有者
	const PlayerCheckAnnihilation& owner_;

	// タイマー
	std::unique_ptr<UiTimer> uiTimer_;
};