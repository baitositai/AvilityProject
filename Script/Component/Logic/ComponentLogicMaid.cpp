#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Character/Enemy/EnemyMaid.h"
#include "../../Object/Item/ItemBase.h"
#include "../../Object/Effect/EffectAirslash.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Collider/ColliderFan.h"
#include "../../Collider/ColliderCircle.h"
#include "../../System/FoodShawer.h"
#include "ComponentLogicMaid.h"

ComponentLogicMaid::ComponentLogicMaid(EnemyMaid& owner):
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter())
{
	moveDirection_ = 0.0f;
	eyeBaseAngle_ = 0.0f;
	stopTimer_ = 0.0f;
	moveDistance_ = {};
	timer_ = 0.0f;
	isMove_ = false;
	isSpecialAttack_ = false;
	specialAttackCount_ = -1;
	specialAttackStartFrame_ = -1;
	timer_ = 0.0f;
	state_ = STATE::COLLECT;
	nextGravityDir_ = ParameterActor::DIR::MAX;

	// 状態遷移処理のマップを初期化
	changeStateMap_.emplace(STATE::COLLECT, std::bind(&ComponentLogicMaid::ChangeStateCollect, this));
	changeStateMap_.emplace(STATE::JUMP, std::bind(&ComponentLogicMaid::ChangeStateJump, this));
	changeStateMap_.emplace(STATE::STAMP_READY, std::bind(&ComponentLogicMaid::ChangeStateStampReady, this));
	changeStateMap_.emplace(STATE::STAMP, std::bind(&ComponentLogicMaid::ChangeStateStamp, this));
	changeStateMap_.emplace(STATE::SPECIAL, std::bind(&ComponentLogicMaid::ChangeStateSpecial, this));
	changeStateMap_.emplace(STATE::TEREPORT, std::bind(&ComponentLogicMaid::ChangeStateTeleport, this));
	changeStateMap_.emplace(STATE::DELAY, std::bind(&ComponentLogicMaid::ChangeStateDelay, this));
}

ComponentLogicMaid::~ComponentLogicMaid()
{
}

void ComponentLogicMaid::Create()
{
	// 視野角用のコライダーを生成
	colliderFan_ = std::make_shared<ColliderFan>(owner_, CollisionTags::TAG::ENEMY_VIEW, owner_.GetParameter().pos_, parameter_.eyeDistance_, eyeBaseAngle_, parameter_.eyeAngleRad_);

	// コライダーの登録
	collisionManager_.Add(colliderFan_);

	// フードシャワー
	FoodShawer::Parameter parameter;
	parameter.interval_ = 2.2f;
	parameter.fallDirList_ = { ParameterActor::DIR::DOWN,ParameterActor::DIR::RIGHT,ParameterActor::DIR::LEFT,ParameterActor::DIR::UP };
	parameter.limitCount_ = 10;
	constexpr int OFFSET = 150;
	parameter.createRangeTopLeft_ = { OFFSET,OFFSET };
	parameter.createRangeBottomRight_ = { Application::SCREEN_SIZE_X - OFFSET, Application::SCREEN_SIZE_Y - OFFSET };
	foodShawer_ = std::make_unique<FoodShawer>(parameter);

	// 初期化処理
	Init();
}

void ComponentLogicMaid::Init()
{
	// 基底クラスの初期化
	ComponentLogicBase::Init();

	// フードシャワー
	foodShawer_->Init();

	// 状態遷移
	ChangeState(STATE::COLLECT);

	// 視野角の初期化
	UpdateEyeAngle();

	// 一番最初で攻撃をさせないため
	isSpecialAttack_ = true;
}

void ComponentLogicMaid::Update()
{
	// 状態別更新
	update_();

	// 状態が生存の場合
	if (owner_.GetState() == CharacterBase::STATE::ALIVE && 
		state_ == STATE::COLLECT)
	{
		// 視野角の更新
		UpdateEyeAngle();

		// アニメーションの更新
		UpdateAnimation();
	}
}

void ComponentLogicMaid::Remove()
{
	if (colliderFan_)
	{
		colliderFan_->Delete();
		colliderFan_ = nullptr;
	}	
	if (colliderCircle_)
	{
		colliderCircle_->Delete();
		colliderCircle_ = nullptr;
	}
}

void ComponentLogicMaid::AttackReset()
{
	if (colliderFan_)
	{
		colliderFan_->SetIsActive(false);
	}
	if (colliderCircle_)
	{
		colliderCircle_->SetIsActive(false);
	}
}

void ComponentLogicMaid::UpdateCollect()
{	
	// 食べ物の取得回数が条件数満たしている場合
	if (parameter_.hitFoodCount_ >= parameter_.triggerFoodCount_)
	{
		ChangeState(STATE::TEREPORT);
		return;
	}

	// 発見判定
	if (parameter_.isDiscover_)
	{
		// 攻撃
		Attack();

		// 終了判定
		isEnd_ = true;

		// 視野コライダー判定を無効
		colliderFan_->SetIsActive(false);

		// ターゲットの発見判定をリセット
		parameter_.isDiscover_ = false;
		return;
	}

	Vector2F moveDir = {};
	float distance = 0.0f;
	ParameterEnemyMaid::DIR gravityDir = parameter_.gravityDir_;

	// フードシャワーの更新
	foodShawer_->Update();

	// 一番近い食べ物を取得
	const ItemBase* targetFood = itemManager_.GetNearestFood(parameter_.pos_);

	if (targetFood)
	{
		// ターゲットへのベクトルと重力方向を取得
		Vector2F diff = Vector2F::SubVector2F(targetFood->GetParameter().pos_, parameter_.pos_);
		distance = diff.Length();

		if (distance > 0.0f)
		{
			moveDir = Vector2F(diff.x / distance, diff.y / distance);
		}

		gravityDir = targetFood->GetParameter().gravityDir_;
	}
	else
	{
		// 最も現在地から近いプレイヤーを取得
		const Player* nearestPlayer = playerManager_.GetNearestPlayer(parameter_.pos_);

		if (nearestPlayer)
		{
			auto& playerParameter = nearestPlayer->GetParameter();

			// プレイヤーへのベクトルと重力方向を取得
			Vector2F diff = Vector2F::SubVector2F(playerParameter.pos_, parameter_.pos_);
			distance = diff.Length();

			if (distance > 0.0f)
			{
				moveDir = Vector2F(diff.x / distance, diff.y / distance);
			}

			// 特殊攻撃（未実行の場合のみ1回発動し、移動自体は継続する）
			if (!isSpecialAttack_)
			{
				CreateAirSlash(moveDir);
				Attack();
				isSpecialAttack_ = true;
			}

			gravityDir = playerParameter.gravityDir_;
		}
	}

	// ターゲットに向かって移動
	if (distance > 0.01f)
	{
		Vector2F velocity = Vector2F::MulVector2FFloat(moveDir, parameter_.moveSpeed_);
		parameter_.moveAmount_ = velocity;
	}

	// タイマーが0未満で、重力方向が変化している場合
	if (timer_ < 0.0f && parameter_.gravityDir_ != gravityDir)
	{
		// スタンプへ切り替えるタイマーをリセット
		timer_ = CHANGE_GRAVITY_TIME;

		// 状態遷移
		ChangeState(STATE::JUMP);

		// 重力方向の更新
		nextGravityDir_ = gravityDir;

		// 攻撃判定オフ
		isSpecialAttack_ = false;
	}
	else
	{
		// タイマーを減算
		timer_ -= sceneManager_.GetDeltaTime();
	}	
	
	// ベクトルの長さを計算して距離を求める
	distance = moveDir.Length();
	
	// ターゲットに向かって移動
	if (distance > 0.01f)
	{
		moveDir = Vector2F(moveDir.x / distance, moveDir.y / distance);
		Vector2F velocity = Vector2F::MulVector2FFloat(moveDir.Normalize(), parameter_.moveSpeed_);
		parameter_.moveAmount_ = velocity;
	}

	// タイマーが0未満で、重力方向が変化している場合
	if(timer_ < 0.0f && parameter_.gravityDir_ != gravityDir)
	{
		// スタンプへ切り替えるタイマーをリセット
		timer_ = CHANGE_GRAVITY_TIME;
		
		// 状態遷移
		ChangeState(STATE::JUMP);	
		
		// 重力方向の更新
		nextGravityDir_ = gravityDir;

		// 攻撃判定オフ
		isSpecialAttack_ = false;
	}
	else
	{
		// タイマーを減算
		timer_ -= sceneManager_.GetDeltaTime();
	}
}

void ComponentLogicMaid::UpdateJump()
{
	// ジャンプ力が一定値以上の場合
	const float HIGHEST = -parameter_.jumpPowMax_ / 2.0f + 2.0f;
	if (parameter_.jumpPow_ >= HIGHEST)
	{
		// 状態遷移
		ChangeState(STATE::STAMP_READY);
	}	
}

void ComponentLogicMaid::UpdateStampReady()
{
	timer_ -= sceneManager_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		ChangeState(STATE::STAMP);
	}
}

void ComponentLogicMaid::UpdateStamp()
{
	if (parameter_.isGround_)
	{
		// 状態遷移
		ChangeState(STATE::COLLECT);

		//カメラシェイク
		SceneManager::GetInstance().GetCamera().SetCameraShake(CAMERA_SHAKE_TIME, CAMERA_SHAKE_POWER);

		// 効果音再生
		soundManager_.PlaySe(SoundType::SE::ABILITY_STAMP_LANDING);

		// エフェクト再生
		SpriteEffectManager::CreateParameter parameter;
		parameter.pos = parameter_.GetFootPos();
		parameter.pos = Vector2F::AddVector2F(parameter.pos, Vector2F::MulVector2FFloat(parameter_.GetUp(), 20.0f));
		parameter.angle = parameter_.angle_;
		parameter.resourceKey = "stampLanding";
		parameter.animationSpeed = 0.3f;
		spriteEffectManager_.Create(parameter);
	
		// 重力をもとに戻す
		parameter_.gravityPower_ -= ADD_GRAVITY;
	}
}

void ComponentLogicMaid::UpdateSpecial()
{
	Animation& animation = owner_.GetAnimation();
	if (animation.IsPlay())
	{
		if(specialAttackStartFrame_ == animation.GetAnimationIndex() && !isSpecialAttack_)
		{
			// エアースラッシュの方向を決定
			Vector2F baseDir = parameter_.GetFront();

			// ランダムな角度を計算
			const float randomValue = static_cast<float>(UtilityCommon::GetRandomCount(0, 100)) / 100.0f;
			const float spreadAngle = (randomValue * 2.0f - 1.0f) * UtilityCommon::Deg2RadF(30.0f);

			// ベクトルを回転させる（2D回転行列の計算）
			const float cosA = cosf(spreadAngle);
			const float sinA = sinf(spreadAngle);

			// 方向を決定
			Vector2F dir = {
				baseDir.x * cosA - baseDir.y * sinA,
				baseDir.x * sinA + baseDir.y * cosA
			};

			// エアースラッシュ生成
			CreateAirSlash(dir);

			// 攻撃判定を有効化
			isSpecialAttack_ = true;

			// 攻撃用コライダーを有効化
			colliderCircle_->SetIsActive(true);
		}
	}
	else
	{
		// 攻撃か数を減らす
		specialAttackCount_--;
		if(specialAttackCount_ <= 0)
		{
			// 状態遷移
			ChangeState(STATE::COLLECT);

			// 攻撃コライダーの削除
			colliderCircle_->Delete();
			colliderCircle_ = nullptr;
			return;
		}

		// 再生するアニメーションを格納
		const std::vector<Animation::TYPE> animationList = { Animation::TYPE::ATTACK, Animation::TYPE::ATTACK_2,Animation::TYPE::ATTACK_3 };

		// アニメーションの攻撃開始番号
		const std::vector<int> attackStartIndexList = { parameter_.defaultAttackStartFrame_, parameter_.defaultAttackStartFrame2_, parameter_.defaultAttackStartFrame3_ };

		// 再生するアニメーションインデックスをランダムで取得
		const int randomIndex = UtilityCommon::GetRandomCount(0, static_cast<int>(animationList.size()) - 1);

		// 攻撃開始番号の設定
		specialAttackStartFrame_ = attackStartIndexList[randomIndex];

		// 攻撃判定を無効にする
		isSpecialAttack_ = false;

		// アニメーション再生
		animation.Play(animationList[randomIndex], false);
	}
}

void ComponentLogicMaid::UpdateTeleport()
{
	timer_ -= sceneManager_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		// 効果音再生
		soundManager_.PlaySe(SoundType::SE::ABILITY_TELEPORT_EXIT);

		// エフェクト再生
		SpriteEffectManager::CreateParameter parameter;
		parameter.pos = parameter_.pos_;
		parameter.angle = parameter_.angle_;
		parameter.resourceKey = "teleportExit";
		parameter.animationSpeed = 0.2f;
		spriteEffectManager_.Create(parameter);

		// 描画
		owner_.SetIsDraw(true);

		// コライダー有効
		owner_.SetColliderActive(true);

		// 状態遷移
		ChangeState(STATE::DELAY);
	}
}

void ComponentLogicMaid::UpdateDelay()
{
	timer_ -= sceneManager_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		ChangeState(STATE::SPECIAL);
	}
}

void ComponentLogicMaid::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void ComponentLogicMaid::ChangeStateCollect()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateCollect, this);

	// 初期アニメーションの再生
	owner_.GetAnimation().Play(Animation::TYPE::IDLE, true);

	// 視野コライダー判定を有効
	colliderFan_->SetIsActive(true);

	// タイマー初期化
	timer_ = CHANGE_GRAVITY_TIME;
}

void ComponentLogicMaid::ChangeStateJump()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateJump, this);
	
	// 視野コライダー判定を無効
	colliderFan_->SetIsActive(false);

	// 地面判定を無効
	parameter_.isGround_ = false;

	// ジャンプ力設定
	owner_.SetJumpPow(-parameter_.jumpPowMax_);

	// 待機アニメーションを再生
	owner_.GetAnimation().Play(Animation::TYPE::JUMP, false);

	// タイマー初期化
	timer_ = STOP_TIME;
}

void ComponentLogicMaid::ChangeStateStampReady()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateStampReady, this);

	// 次の重力を設定
	parameter_.gravityDir_ = nextGravityDir_;

	// 角度の更新
	parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(nextGravityDir_);

	// ジャンプ力を0にする
	owner_.SetJumpPow(0.0f);

	// ジャンプアニメーション
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);

	// 重力を無効化
	owner_.SetComponentActive("gravity", false);

	// 衝突判定を行うために無理やり移動量を追加
	parameter_.moveAmount_.x += 0.1f;

	// 効果音再生
	soundManager_.PlaySe(SoundType::SE::ABILITY_STAMP_CHARGE);

	// エフェクト
	SpriteEffectManager::CreateParameter parameter;
	parameter.pos = parameter_.pos_;
	parameter.angle = parameter_.angle_;
	parameter.resourceKey = "stampCharge";
	parameter.animationSpeed = 0.3f;
	spriteEffectManager_.Create(parameter);
}

void ComponentLogicMaid::ChangeStateStamp()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateStamp, this);

	// 重力を加速
	parameter_.gravityPower_ += ADD_GRAVITY;

	// 重力を有効化
	owner_.SetComponentActive("gravity", true);
}

void ComponentLogicMaid::ChangeStateSpecial()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateSpecial, this);

	// 攻撃回数を設定
	specialAttackCount_ = SPECIAL_ATTACK_COUNT;

	// 攻撃判定無効
	isSpecialAttack_ = false;

	// アニメーション設定
	owner_.GetAnimation().Play(Animation::TYPE::ATTACK, false);

	// 攻撃開始番号を設定
	specialAttackStartFrame_ = parameter_.defaultAttackStartFrame_;

	// 取得回数リセット
	parameter_.hitFoodCount_ = 0;

	// 攻撃者の前方向を取得
	Vector2F dir = Vector2F::MulVector2FFloat(parameter_.GetFront(), parameter_.scale_);
	specialAttackPos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(dir, parameter_.defaultAttackDistance_));

	// コライダーの登録
	colliderCircle_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, specialAttackPos_, parameter_.defaultAttackRadius_);
	collisionManager_.Add(colliderCircle_);
}

void ComponentLogicMaid::ChangeStateTeleport()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateTeleport, this);

	// 移動前位置でエフェクト再生
	SpriteEffectManager::CreateParameter parameter;
	parameter.pos = parameter_.pos_;
	parameter.angle = parameter_.angle_;
	parameter.resourceKey = "teleportEnter";
	parameter.animationSpeed = 0.2f;
	spriteEffectManager_.Create(parameter);

	// 移動
	parameter_.pos_ = { 150.0f, Application::SCREEN_SIZE_Y - 180 };
	parameter_.gravityDir_ = ParameterActor::DIR::DOWN;
	parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);
	parameter_.direction_ = false;
	owner_.SetIsDraw(false);
	owner_.SetColliderActive(false);

	// テレポート時間設定
	timer_ = TEREPORT_TIME;

	// アニメーション変更
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);

}

void ComponentLogicMaid::ChangeStateDelay()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateDelay, this);

	// 遅延時間の指定
	timer_ = SPECIAL_ATTACK_DELAY_TIME;
}

void ComponentLogicMaid::UpdateEyeAngle()
{
	// キャラクターの向きに応じてコライダーの角度を更新
	eyeBaseAngle_ = parameter_.angle_;
	eyeBaseAngle_ += parameter_.direction_ ? DX_PI_F : 0.0f;
}

void ComponentLogicMaid::UpdateAnimation()
{
	Animation& animation = owner_.GetAnimation();
	Animation::TYPE type = Animation::TYPE::MAX;

	// 移動しているかどうかの判定
	if (parameter_.moveAmount_.x != 0.0f || parameter_.moveAmount_.y != 0.0f)
	{
		type = Animation::TYPE::WALK;

		// 重力方向に応じて、チェックする移動量の軸を切り替える
		if (parameter_.gravityDir_ == ParameterActor::DIR::DOWN)
		{
			// 通常（地面）：右移動で通常、左移動で反転
			parameter_.direction_ = (parameter_.moveAmount_.x < 0.0f);
		}
		else if (parameter_.gravityDir_ == ParameterActor::DIR::UP)
		{
			// 天井：通常とは上下反転しているため、左移動で通常、右移動で反転
			parameter_.direction_ = (parameter_.moveAmount_.x > 0.0f);
		}
		else if (parameter_.gravityDir_ == ParameterActor::DIR::LEFT)
		{
			// 左の壁：上に向かって進むときが通常、下に向かって進むときが反転
			parameter_.direction_ = (parameter_.moveAmount_.y < 0.0f);
		}
		else if (parameter_.gravityDir_ == ParameterActor::DIR::RIGHT)
		{
			// 右の壁：下に向かって進むときが通常、上に向かって進むときが反転
			parameter_.direction_ = (parameter_.moveAmount_.y > 0.0f);
		}
	}
	else
	{
		type = Animation::TYPE::IDLE;
	}

	if (animation.GetType() == type)
	{
		return;
	}

	animation.Play(type);
}

void ComponentLogicMaid::Attack()
{
	// 状態遷移
	owner_.ChangeState(EnemyMaid::STATE::ATTACK);

	// 攻撃のアニメーションを開始（ループしない）
	owner_.GetAnimation().Play(Animation::TYPE::ATTACK, false);

	// 次回アニメーションを指定しない
	owner_.GetAnimation().SetNextAnimationType(Animation::TYPE::MAX);

	// 攻撃判定
	parameter_.isAction_ = true;
}

void ComponentLogicMaid::CreateAirSlash(const Vector2F& dir)
{	
	std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();
	parameter->pos_ = parameter_.pos_;
	parameter->gravityDir_ = parameter_.gravityDir_;
	parameter->angle_ = std::atan2f(dir.y, dir.x);
	parameter->hitRadius_ = 16.0f * parameter_.scale_;
	parameter->resourceKey_ = "airslash";
	parameter->scale_ = parameter_.scale_;
	parameter->divisionNum_ = { 4, 1 };
	parameter->transparent_ = true;
	parameter->moveSpeed_ = 10.0f;
	parameter->attackPower_ = parameter_.attackPower_;
	parameter->attackBoostRate_ = parameter_.attackBoostRate_;
	parameter->componentkeys_ = { "spriteAnimation" };
	parameter->tag_ = CollisionTags::TAG::ENEMY_ATTACK_NORMAL;
	parameter->color_ = VECTOR{ 1.0f, 0.1f, 1.5f };
	parameter->animationDataMap_.emplace("effect", Animation::Data(0, 3, 0.3));
	std::unique_ptr<EffectAirslash> effect = std::make_unique<EffectAirslash>(std::move(parameter), dir);
	spriteEffectManager_.Add(std::move(effect));
}