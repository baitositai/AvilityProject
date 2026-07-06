#pragma once
#include "../ActorBase.h"

class Train : public ActorBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	Train(std::unique_ptr<ParameterActor> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Train() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	ParameterActor* parameterTrain_;
};