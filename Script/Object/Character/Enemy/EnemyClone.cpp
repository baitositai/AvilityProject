#include <DxLib.h>
#include "../../../Utility/UtilityCommon.h"
#include "../../../Collider/ColliderBox.h"
#include "../../../OnHit/OnHitEnemyClone.h"
#include "../../Common/Animation.h"
#include "EnemyClone.h"

EnemyClone::EnemyClone(std::unique_ptr<ParameterEnemyClone> parameter) :
	CharacterBase(std::move(parameter))
{
	// プレイヤー用のパラメータ
	parameterEnemy_ = dynamic_cast<ParameterEnemyClone*>(GetParameterCharacterPtr());
	assert(parameterEnemy_ != nullptr);
}

EnemyClone::~EnemyClone()
{
}

void EnemyClone::Init()
{
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_CLONE, parameterEnemy_->pos_, parameterEnemy_->hitSize_, parameterEnemy_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEnemyClone>(*this);

	// 基底クラスの初期化
	CharacterBase::Init();

	animation_->Play(Animation::TYPE::IDLE);
}

void EnemyClone::DebugDraw()
{
	CharacterBase::DebugDraw();
	Vector2 k = parameterEnemy_->knockBackPower_.ToVector2();
	DrawFormatString(0, 80, UtilityCommon::BLACK, L"敵kb:%d,%d", k.x, k.y);
}