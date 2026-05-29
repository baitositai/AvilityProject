#include <tgmath.h>
#include "../../Utility/UtilityCommon.h"
#include "../../Common/Vector2F.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Collider/ColliderBox.h"

#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Player.h"
#include "../../Object/ActorBase.h"

#include "ComponentAvilityLaser.h"

#include "../../Parameter/Effect/ParameterEffect.h"
#include "../../Object/Effect/EffectLaser.h"
#include "../../Manager/Common/SpriteEffectManager.h"

ComponentAvilityLaser::ComponentAvilityLaser(Player& owner)
	: ComponentAvilityBase(owner),
	collisionManager_(CollisionManager::GetInstance()),
	inputManager_(InputManager::GetInstance()),
	moveAmount_({}),
	chageTime_(0.0f),
	shotTime_(0.0f),
	shotVec_({}),
	shotAngle_(0.0f)
{

	// コライダーの登録
	attackCollider_ = owner_.CreateColliderClone();
	attackCollider_->ChangeTag(CollisionTags::TAG::PLAYER_AVILITY_SHOT);
	attackCollider_->SetIsActive(false);
	CollisionManager::GetInstance().Add(attackCollider_);

	abilitySlot_ = ABILITY_SLOT::FIRST;
	type_ = AvilityTypes::TYPE::SHOT;
	stateFunctionMap_ =
	{
		{"input", [this]() { return ProcessInputShot(); }},		// 入力待ち状態
		{"charge", [this]() { return ProcessInputCharge(); }},	// チャージ状態
	};
	currentState_ = "input";
	currentStateFunction_ = stateFunctionMap_[currentState_];
}

ComponentAvilityLaser::~ComponentAvilityLaser()
{
}

void ComponentAvilityLaser::Init()
{
	// 状態の初期化
	currentState_ = "input";
	currentStateFunction_ = stateFunctionMap_[currentState_];

	// 自身のコライダーの判定を有効にする
	owner_.SetColliderActive(true);

	// コンポーネントの活動状態を戻す
	owner_.SetComponentActive("gravity", true);
	owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

	// 攻撃判定用コライダーを無効にする
	attackCollider_->SetIsActive(false);

	shotVec_ = {};
	shotAngle_ = 0.0f;

	parameter_.shotVec_ = {};
}

void ComponentAvilityLaser::Update()
{
	// バウンドで停止したよう
	if (!isActive_) {

		return;
	}

	// 移動量の初期化
	moveAmount_ = {};
	moveAmount_ = parameter_.moveAmount_;

	// パラメータの取得
	pos_ = parameter_.pos_;
	defaultSize_ = parameter_.hitSize_;
	gravityDir_ = parameter_.gravityDir_;

	// 重力方向に合わせたサイズ調整
	bool isVerticalGravity = (gravityDir_ == ParameterActor::DIR::UP || gravityDir_ == ParameterActor::DIR::DOWN);
	nowSize_.x = isVerticalGravity ? defaultSize_.x : defaultSize_.y;
	nowSize_.y = isVerticalGravity ? defaultSize_.y : defaultSize_.x;

	// 状態関数の呼び出し
	currentStateFunction_();

}

void ComponentAvilityLaser::Remove()
{
	// コライダーの削除 
	if (attackCollider_)
	{
		attackCollider_->Delete();
	}

	// 攻撃力を戻す
	//owner_.AddAttackPower(-ADD_ATTACK_POWER);
}

void ComponentAvilityLaser::ProcessInputShot()
{
	// 横向きにしか撃てないようにするため、縦の入力は無視する
	const float moveSpeed = parameter_.moveSpeed_;

	//　ショット入力があったらCharge開始(現在Qキー)
	if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_AVILITY_SHOT))
	{
		// 影響を与えるコンポーネントを無効にする
		owner_.SetStateComponentActive(Player::STATE::ALIVE, false);
		owner_.SetComponentActive("gravity", false);

		// ジャンプ力をなくす
		parameter_.jumpPow_ = 0.0f;

		shotTime_ = 0.0f;
		// 状態の遷移
		currentState_ = "charge";
		currentStateFunction_ = stateFunctionMap_[currentState_];
	}
}

void ComponentAvilityLaser::ProcessInputCharge()
{

	// =========================
	// チャージ
	// =========================

	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_AVILITY_SHOT))
	{
		chageTime_ += 0.5f;
		shotTime_ += 0.1f;

		moveAmount_.x = std::sin(chageTime_);
		moveAmount_.y = 0.0f;

		parameter_.moveAmount_ = moveAmount_;
	}
	else
	{

		// チャージが終了したときの処理
		if (shotTime_ > HI_LASER_COUNT)
		{
			CreateHiLaser();
		}

		// 自身のコライダーの判定を有効にする
		owner_.SetColliderActive(true);

		// コンポーネントの活動状態を戻す
		owner_.SetComponentActive("gravity", true);
		owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

		// 攻撃判定用コライダーを無効にする
		attackCollider_->SetIsActive(false);

		currentState_ = "input";
		currentStateFunction_ = stateFunctionMap_[currentState_];

	}

}

void ComponentAvilityLaser::CreateHiLaser()
{
	constexpr int CREATE_NUM = 1;		// 生成するエフェクトの数
	constexpr float SPREAD_WIDTH = 0.5f;// エフェクトの広がり具合を調整する定数

	// 基準となる重力下方向ベクトルを取得
	const Vector2F downDir = parameter_.GetDown();

	// 右方向
	const Vector2F rightDir = { -downDir.y, downDir.x };

	// 方向を調整
	const Vector2F dirRightSlash = Vector2F::MulVector2FFloat(rightDir, SPREAD_WIDTH);
	const Vector2F dirLeftSlash = Vector2F::MulVector2FFloat(rightDir, -SPREAD_WIDTH);

	const Vector2F dir = parameter_.direction_ ? dirRightSlash : dirLeftSlash;

	// 描画角度の計算
	float angle = std::atan2f(dir.y, dir.x);
	// 補正値
	//float correctionAngle = UtilityCommon::Deg2RadF(-90.0f); // 必要に応じて調整
	parameter_.direction_ ? angle += UtilityCommon::Deg2RadF(90.0f) : angle -= UtilityCommon::Deg2RadF(-90.0f);

	for (int i = 0; i < CREATE_NUM; i++)
	{
		// 弾エフェクトのパラメータ設定
		std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();
		parameter->pos_ = parameter_.pos_;
		parameter->gravityDir_ = parameter_.gravityDir_;
		parameter->angle_ = angle;
		parameter->hitRadius_ = 16.0f;
		parameter->resourceKey_ = "Leaser3";
		parameter->scale_ = 1.0f;
		parameter->divisionNum_ = { 9, 30 };
		parameter->transparent_ = true;
		parameter->moveSpeed_ = 0.0f;
		parameter->attackPower_ = parameter_.attackPower_;
		parameter->attackBoostRate_ = parameter_.attackBoostRate_;
		parameter->componentkeys_ = { "spriteAnimation" };
		parameter->animationDataMap_.emplace("effect", Animation::Data(9 * 20, 9 * 20 + 8, 0.1));
		// エフェクトの生成と追加
		std::unique_ptr<EffectLaser> effect = std::make_unique<EffectLaser>(std::move(parameter), dir, 20);
		SpriteEffectManager::GetInstance().Add(std::move(effect));
	}
	chageTime_ = 0.0f;
}

void ComponentAvilityLaser::CreateLaser(float _ChageTime)
{
	chageTime_ = 0.0f;
}

