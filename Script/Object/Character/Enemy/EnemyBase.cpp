#include <DxLib.h>
#include "../../../Utility/UtilityCommon.h"
#include "../../../Manager/Common/SceneManager.h"
#include "../../../Manager/Game/ItemManager.h"
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

void EnemyBase::DropItem()
{
	ItemManager& itemManager = ItemManager::GetInstance();

	// アイテムを生成する
	itemManager.CreateMoneyItem(parameterEnemy_->dropMoney_, parameterEnemy_->pos_);

	// ランダム確率でほかのアイテムも生成
	int probability = GetRand(15);

	if (probability < 3)
	{
		itemManager.CreateFoodItem(static_cast<ItemTypes::FOOD_TYPE>(GetRand(ItemTypes::FOOD_TYPE_MAX - 1)), parameterEnemy_->pos_);
	}
	else if (probability == 3)
	{
		itemManager.CreateAvilityItem(static_cast<AvilityTypes::TYPE>(GetRand(AvilityTypes::AVILITY_TYPE_MAX - 1)), parameterEnemy_->pos_);
	}
	else if (probability == 4)
	{
		itemManager.CreateTreasureItem(static_cast<ItemTypes::TREASURE_TYPE>(GetRand(ItemTypes::TREASURE_TYPE_MAX - 1)), parameterEnemy_->pos_);
	}
}

void EnemyBase::Damage(const int damage, const Vector2& hitPos)
{	
	// 基底クラスの処理
	CharacterBase::Damage(damage, hitPos);
	
	// ダメージを受けている場合はダメージ描画用のステップを設定
	damageDrawStep_ = DAMAGE_DRAW_STEP_MAX;	
}