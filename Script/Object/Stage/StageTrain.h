#pragma once
#include "Stage.h"

class ColliderBox;

class StageTrain : public Stage
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	StageTrain(std::unique_ptr<ParameterStage> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageTrain() override;

private:

	std::shared_ptr<ColliderBox> colliderBox_;

	// パラメータ情報
	ParameterStage* parameterStageTrain_;

};

