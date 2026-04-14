#pragma once
#include "GameStateBase.h"

class GameStateEvent :  public GameStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stage">ステージクラス</param>
	GameStateEvent(Stage& stage);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStateEvent() override;

};

