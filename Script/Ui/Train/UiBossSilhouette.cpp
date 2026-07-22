#include <DxLib.h>
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "UiBossSilhouette.h"

UiBossSilhouette::UiBossSilhouette() :
	enemyManager_(EnemyManager::GetInstance())
{
	handles_ = nullptr;
}

UiBossSilhouette::~UiBossSilhouette()
{
}

void UiBossSilhouette::Init()
{
	handles_ = resourceManager_.GetHandles("bossSilhouette");
	scale_ = 1.0f;
	pos_ = {302, 321};
}

void UiBossSilhouette::Draw()
{
	const int index = RES_INDEX_MAP.at(enemyManager_.GetBossEnemyType());
	Vector2F cameraPos = mainCamera.GetPos();
	Vector2 drawPos = pos_ + cameraPos.ToVector2();

	DrawRotaGraph(
		drawPos.x,
		drawPos.y,
		scale_,
		0.0f,
		handles_[index],
		true
	);
}
