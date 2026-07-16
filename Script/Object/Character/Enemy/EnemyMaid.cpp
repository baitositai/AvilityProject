#include "../../../Manager/Common/SoundManager.h"
#include "../../../Manager/Common/SpriteEffectManager.h"
#include "../../../OnHit/OnHitEnemyMaid.h"
#include "../../../Collider/ColliderBox.h"
#include "EnemyMaid.h"

EnemyMaid::EnemyMaid(std::unique_ptr<ParameterEnemyMaid> parameter) :
	EnemyBoss(std::move(parameter))
{
	// 専用のパラメータ
	parameterEnemyMaid_ = dynamic_cast<ParameterEnemyMaid*>(GetParameterEnemyBossPtr());
	assert(parameterEnemyMaid_ != nullptr);
}

EnemyMaid::~EnemyMaid()
{
}

void EnemyMaid::Init()
{
	// 敵のヒットサイズ拡大
	parameterEnemyMaid_->hitSize_ = parameterEnemyMaid_->GetScaleToHitSize();

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_MAID, parameterEnemyMaid_->pos_, parameterEnemyMaid_->hitSize_, parameterEnemyMaid_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEnemyMaid>(*this);

	// 攻撃用のタグの設定
	parameterEnemyMaid_->attackCollisionTag_ = CollisionTags::TAG::ENEMY_ATTACK_NORMAL;

	// 基底クラスの初期化
	CharacterBase::Init();
}