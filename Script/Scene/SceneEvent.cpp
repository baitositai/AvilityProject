#include "SceneEvent.h"

SceneEvent::SceneEvent()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneEvent::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneEvent::LoadingDraw, this);
}

SceneEvent::~SceneEvent()
{
}

void SceneEvent::Init()
{
}

void SceneEvent::NormalUpdate()
{
}

void SceneEvent::NormalDraw()
{
}

void SceneEvent::DebugUpdate()
{
}

void SceneEvent::DebugDraw()
{
}
