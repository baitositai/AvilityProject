#include <DxLib.h>
#include "../../../Utility/UtilityCommon.h"
#include "../../../Manager/Common/SceneManager.h"
#include "../../../Manager/Common/ResourceManager.h"
#include "../../../Manager/Game/ItemManager.h"
#include "../../../Collider/ColliderBox.h"
#include "../../../OnHit/OnHitEnemy.h"
#include "../../../Resource/ResourceTexture.h"
#include "../../../Render/PixelMaterial.h"
#include "../../../Render/PixelRenderer.h"
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
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_BASE, parameterEnemy_->pos_, parameterEnemy_->hitSize_, parameterEnemy_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEnemy>(*this);

	// 攻撃用のタグの設定
	parameterEnemy_->attackCollisionTag_ = CollisionTags::TAG::ENEMY_ATTACK_NORMAL;

	// 基底クラスの初期化
	CharacterBase::Init();
}

void EnemyBase::Draw()
{
	if (damageDrawStep_ > 0.0f)
	{
		damageDrawStep_ -= scnMng_.GetDeltaTime();
		float damageRatio = damageDrawStep_ / DAMAGE_DRAW_STEP_MAX;
		// 赤く光らせる
		parameterEnemy_->damageColor_ = VECTOR(damageRatio, 0.0f, 0.0f);
	}
	else
	{
		// ダメージ色をなくす
		parameterEnemy_->damageColor_ = VECTOR(0.0f, 0.0f, 0.0f);
	}
	// 追加の定数バッファの更新
	material_->SetConstBuf(3, FLOAT4{ parameterEnemy_->damageColor_.x,parameterEnemy_->damageColor_.y,parameterEnemy_->damageColor_.z,0.0f });

	// 基底クラスの描画
	CharacterBase::Draw();

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

void EnemyBase::InitDraw()
{
	// リソースの取得と同時に必要な情報を取得
	const auto texture = resMng_.GetResourceTexture(parameterEnemy_->resourceKey_);
	parameterEnemy_->drawSize_ = texture->GetSize();
	parameterEnemy_->divisionNum_ = texture->GetDivsion();
	parameterEnemy_->drawHalfSize_ = Vector2(parameterEnemy_->drawSize_.x / 2, parameterEnemy_->drawSize_.y / 2);

	// X軸の反転
	float isReverseX = parameterEnemy_->direction_ ? 1.0f : 0.0f;

	// 基底クラスではスプライト画像を前提で用意
	// マテリアルの生成
	material_ = std::make_unique<PixelMaterial>(resMng_.GetHandle("enemySprite"), CONST_BUFFER_SIZE);
	material_->AddTextureBuf(parameterEnemy_->texture_);
	material_->AddConstBuf(FLOAT4{ parameterEnemy_->color_.x, parameterEnemy_->color_.y,parameterEnemy_->color_.z, parameterEnemy_->alpha_ });
	material_->AddConstBuf(FLOAT4{ isReverseX, 0.0f, parameterEnemy_->angle_,parameterEnemy_->drawIndex_ });
	material_->AddConstBuf(FLOAT4{ (float)parameterEnemy_->divisionNum_.x, (float)parameterEnemy_->divisionNum_.y, 0.0f, 0.0f });
	material_->AddConstBuf(FLOAT4{ 0.0f, 0.0f, 0.0f, 0.0f });

	// レンダラーの生成
	renderer_ = std::make_unique<PixelRenderer>(*material_);

	// 描画サイズを現在のスケールに合わせる
	Vector2 nowSize = Vector2F::MulVector2FFloat(parameterEnemy_->drawSize_.ToVector2F(), parameterEnemy_->scale_).ToVector2();

	// 中心位置に設定
	parameterEnemy_->drawPos_ = GetDrawCenterPos(nowSize);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameterEnemy_->drawPos_, nowSize);
}