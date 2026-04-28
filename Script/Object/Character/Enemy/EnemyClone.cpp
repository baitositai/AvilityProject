#include <DxLib.h>
#include "../../../Utility/UtilityCommon.h"
#include "../../../Collider/ColliderBox.h"
#include "../../../OnHit/OnHitEnemyClone.h"
#include "../../Common/Animation.h"
#include "EnemyClone.h"

EnemyClone::EnemyClone(const Parameter& parameter, const std::unordered_map<std::string, std::string> stateComponentNameList, const std::vector<std::string> defaultComponentNameList, std::unique_ptr<Animation> animation) :
	parameter_(parameter),
	CharacterBase(&parameter_, stateComponentNameList, defaultComponentNameList, std::move(animation))
{
}

EnemyClone::~EnemyClone()
{
}

void EnemyClone::Init()
{
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_CLONE, parameter_.pos, parameter_.hitBoxSize, parameter_.angle);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEnemyClone>(*this);

	// 基底クラスの初期化
	CharacterBase::Init();
}

void EnemyClone::DebugDraw()
{
	CharacterBase::DebugDraw();
	Vector2 k = parameter_.knockBackPower.ToVector2();
	DrawFormatString(0, 80, UtilityCommon::BLACK, L"敵kb:%d,%d", k.x, k.y);
}