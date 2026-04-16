#pragma once
#include "GameStateBase.h"

class GameStateEvent :  public GameStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameStateEvent();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStateEvent() override;

};