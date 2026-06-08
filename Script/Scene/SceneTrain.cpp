#include "SceneTrain.h"

SceneTrain::SceneTrain()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneTrain::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneTrain::LoadingDraw, this);
}

SceneTrain::~SceneTrain()
{
}

void SceneTrain::Init()
{
}

void SceneTrain::NormalUpdate()
{
	SceneBase::NormalUpdate();
}

void SceneTrain::NormalDraw()
{
	SceneBase::NormalDraw();
}

void SceneTrain::DebugUpdate()
{
	SceneBase::DebugUpdate();
}

void SceneTrain::DebugDraw()
{
	SceneBase::DebugDraw();
}