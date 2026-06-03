#include "../../../Utility/UtilityCommon.h"
#include "../../../Manager/Common/SceneManager.h"
#include "../../../Collider/ColliderBox.h"
#include "../../../OnHit/OnHitEnemy.h"
#include "../../../Parameter/Character/Enemy/ParameterEnemy.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(std::unique_ptr<ParameterEnemy> parameter) :
	CharacterBase(std::move(parameter))
{
	damageDrawStep_ = 0.0f;

	// パラメータ情報
	parameterEnemy_ = dynamic_cast<ParameterEnemy*>(GetParameterCharacterPtr());
	assert(parameterEnemy_ != nullptr);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	// 敵のヒットサイズ拡大
	parameterEnemy_->hitSize_ = parameterEnemy_->GetScaleToHitSize();

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_CLONE, parameterEnemy_->pos_, parameterEnemy_->hitSize_, parameterEnemy_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEnemy>(*this);

	// 攻撃用のタグの設定
	parameterEnemy_->attackCollisionTag_ = CollisionTags::TAG::ENEMY_ATTACK_NORMAL;

	// 基底クラスの初期化
	CharacterBase::Init();

	// 初期アニメーション
	animation_->Play(Animation::TYPE::IDLE);
}

void EnemyBase::Draw()
{
	// ダメージを受けている場合
	if (damageDrawStep_ > 0)
	{
		damageDrawStep_ -= scnMng_.GetDeltaTime();

		// 赤くする
		int red = static_cast<int>(255 * damageDrawStep_ / DAMAGE_DRAW_STEP_MAX);
		SetDrawAddColor(red, 0, 0);
	}
	// 基底クラスの描画
	CharacterBase::Draw();

	// 加算した値を戻す
	SetDrawAddColor(0, 0, 0);
}

void EnemyBase::Damage(const int damage)
{	
	// 体力を減らす（ダメージ率だけダメージ量を変える）
	parameterEnemy_->hp_ -= damage * (1 + parameterEnemy_->damageRate_);

	// ダメージを受けている場合はダメージ描画用のステップを設定
	damageDrawStep_ = DAMAGE_DRAW_STEP_MAX;

	// 体力が0以下の場合
	if (parameterEnemy_->hp_ <= 0)
	{
		// 死亡処理
		Dead();
		return;
	}
	
	// 状態遷移
	ChangeState(STATE::ALIVE);
}