#pragma once
#include "GameStateBase.h"
class GameStateBoss : public GameStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameStateBoss();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStateBoss() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

};

