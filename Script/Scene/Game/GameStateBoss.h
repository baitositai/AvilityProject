#pragma once
#include "GameStateBase.h"
class GameStateBoss : public GameStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stage">ステージ</param>
	GameStateBoss(Stage& stage);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStateBoss() override;

};

