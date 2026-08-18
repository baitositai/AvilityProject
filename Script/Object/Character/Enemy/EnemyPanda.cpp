#include "../../../Collider/ColliderBox.h"
#include "../../../OnHit/OnHitEnemyPanda.h"
#include "../../../Manager/Common/SoundManager.h"
#include "../../Common/Animation.h"
#include "EnemyPanda.h"

EnemyPanda::EnemyPanda(std::unique_ptr<ParameterEnemyPanda> parameter) :
	EnemyBoss(std::move(parameter))
{
	// 専用のパラメータ
	parameterEnemyPanda_ = dynamic_cast<ParameterEnemyPanda*>(GetParameterEnemyBossPtr());
	assert(parameterEnemyPanda_ != nullptr);
}

EnemyPanda::~EnemyPanda()
{
}

void EnemyPanda::Init()
{
	// 敵のヒットサイズ拡大
	parameterEnemyPanda_->hitSize_ = parameterEnemyPanda_->GetScaleToHitSize();

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_BASE, parameterEnemyPanda_->pos_, parameterEnemyPanda_->hitSize_, parameterEnemyPanda_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEnemyPanda>(*this);

	// 攻撃用のタグの設定
	parameterEnemyPanda_->attackCollisionTag_ = CollisionTags::TAG::ENEMY_ATTACK_NORMAL;

	// 基底クラスの初期化
	CharacterBase::Init();
}

void EnemyPanda::Update()
{
	// 移動後の値を初期化
	parameterEnemyPanda_->moveAmount_ = {};

	// ディフェンスアニメーション再生中
	if (animation_->GetType() == Animation::TYPE::DEFENCE)
	{
		// 終了した場合
		if (!animation_->IsPlay())
		{
			// 攻撃初期化
			AttackReset();

			// 次回アニメーションを指定
			animation_->SetNextAnimationType(Animation::TYPE::MAX);
		}
	}
	else
	{
		// 状態別コンポーネント処理
		UpdateComponentState();
	}
	
	// 基底クラスの処理
	ActorBase::Update();
}

void EnemyPanda::Defence()
{
	// 現在のアニメーションタイプを取得
	Animation::TYPE type = animation_->GetType();

	// アニメーションの種類が防御の場合待機を指定
	if (type != Animation::TYPE::DEFENCE)
	{
		// 次回アニメーションを指定
		animation_->SetNextAnimationType(type, animation_->IsLoop());
	}
	else if (type == Animation::TYPE::DEFENCE)
	{
		return;
	}
	
	// アニメーション処理
	animation_->Play(Animation::TYPE::DEFENCE, false);

	// 効果音再生
	sndMng_.PlaySe(SoundType::SE::SWORDS_CLASH);

	// 後ろ方向に少し引き下がる
	parameterEnemyPanda_->knockBackPower_ = Vector2F::MulVector2FFloat(parameterEnemyPanda_->GetBack(), 30.0f);
}
