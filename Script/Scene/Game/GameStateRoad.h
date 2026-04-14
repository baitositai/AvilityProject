#pragma once
#include "GameStateBase.h"
class GameStateRoad : public GameStateBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stage">ステージクラス</param>
	GameStateRoad(Stage& stage);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStateRoad() override;

private:

};

