#pragma once
#include "UiPlayerBase.h"

class UiPlayerRespawnMessage : public UiPlayerBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー</param>
	UiPlayerRespawnMessage(const Player& player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiPlayerRespawnMessage() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Update() override;

private:

	// 拡大率
	static constexpr float SCALE_RATE = 0.03f;
	
	// 最大スケール
	static constexpr float SCALE_MAX = 1.2f;
	
	// 最小スケール
	static constexpr float SCALE_MIN = 0.8f;

	// スケール調整用
	float rate_;
};

