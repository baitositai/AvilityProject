#include "../../Utility/UtilityCommon.h"
#include "../../Common/Vector2F.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Collider/ColliderBox.h"

#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Player.h"
#include "../../Object/ActorBase.h"

#include "ComponentAvilityChargeShot.h"

ComponentAvilityChargeShot::ComponentAvilityChargeShot(Player& owner)
	: ComponentAvilityBase(owner),
	collisionManager_(CollisionManager::GetInstance()),
	inputManager_(InputManager::GetInstance()),
	moveAmount_({}),
	chageTime_(0.0f),
	shotTime_(0.0f),
	shotVec_({}),
	shotAngle_(0.0f),
	isReflected_(false),
	reflectCount_(0)
{

	// コライダーの登録
	attackCollider_ = owner_.CreateColliderClone();
	attackCollider_->ChangeTag(CollisionTags::TAG::PLAYER_AVILITY_SHOT);
	attackCollider_->SetIsActive(false);
	CollisionManager::GetInstance().Add(attackCollider_);

	abilitySlot_ = ABILITY_SLOT::FIRST;
	stateFunctionMap_ =
	{
		{"input", [this]() { return ProcessInputShot(); }},		// 入力待ち状態
		{"charge", [this]() { return ProcessInputCharge(); }},	// チャージ状態
		{"shot", [this]() { return ProcessMoveShot(); }}		// ショット移動状態
	};
	currentState_ = "input";
	currentStateFunction_ = stateFunctionMap_[currentState_];
}

ComponentAvilityChargeShot::~ComponentAvilityChargeShot()
{
}

void ComponentAvilityChargeShot::Update()
{
	// バウンドで停止したよう
	if(!isActive_)	{

		return;
	}

	// 移動量の初期化
	moveAmount_ = {};

	const auto& params = *owner_.GetParameter();
	moveAmount_ = params.moveAmount;

	// パラメータの取得
	pos_ = params.pos;
	defaultSize_ = params.hitSize;
	gravityDir_ = params.gravityDir;

	// 重力方向に合わせたサイズ調整
	bool isVerticalGravity = (gravityDir_ == ActorBase::DIR::UP || gravityDir_ == ActorBase::DIR::DOWN);
	nowSize_.x = isVerticalGravity ? defaultSize_.x : defaultSize_.y;
	nowSize_.y = isVerticalGravity ? defaultSize_.y : defaultSize_.x;

	// 状態関数の呼び出し
	currentStateFunction_();

}

void ComponentAvilityChargeShot::Remove()
{
	// コライダーの削除 
	if (attackCollider_)
	{
		attackCollider_->SetDelete();
	}

	// 攻撃力を戻す
	//owner_.AddAttackPower(-ADD_ATTACK_POWER);
}

void ComponentAvilityChargeShot::ProcessInputShot()
{
	// 横向きにしか撃てないようにするため、縦の入力は無視する
	const float moveSpeed = owner_.GetParameter()->moveSpeed;

	//　ショット入力があったらCharge開始(現在Qキー)
	if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_AVILITY))
	{
		owner_.SetComponentActive("AvilityShot", false);

		!owner_.GetParameter()->direction ? shotAngle_ = UtilityCommon::Deg2RadF(0.0f) : shotAngle_ = UtilityCommon::Deg2RadF(180.0f);

		shotTime_ = 0.0f;
		currentState_ = "charge";
		currentStateFunction_ = stateFunctionMap_[currentState_];
	}
}

void ComponentAvilityChargeShot::ProcessInputCharge()
{
	shotVec_ = {};
	float angle = 0.0f;

	// 現在の向きを入れる
	shotVec_.x = owner_.GetParameter()->direction ? -1 : 1;

	// =========================
	// ここで角度を決定
	// 方向判定
	if (inputManager_.IsNew(InputManager::TYPE::AVILITY_GRAVITY_RIGHT))
	{
		shotAngle_ += 0.1f;
	}
	if (inputManager_.IsNew(InputManager::TYPE::AVILITY_GRAVITY_LEFT))
	{
		shotAngle_ -= 0.1f;
	}

	if (shotAngle_ > UtilityCommon::Deg2RadF(360.0f))
	{
		shotAngle_ = 0.0f;
	}

	// =========================
	// 角度 → ベクトル
	// =========================

	shotVec_.x = std::cos(shotAngle_);
	shotVec_.y = std::sin(shotAngle_);


	// 正規化不要
	// cos/sinは長さ1

	owner_.SetShotVec(shotVec_);

	// =========================
	// 向き
	// =========================
	
	// 現在の向きに応じて方向を設定
	//shotVec_.x > 0 ? owner_.SetDirection(false) : owner_.SetDirection(true);

	angle = shotAngle_;

	// -PI ～ PI の範囲に正規化
	/*while (angle <= -DX_PI_F) angle += DX_TWO_PI_F;
	while (angle > DX_PI_F) angle -= DX_TWO_PI_F;*/

	// 左向き判定
	//if (std::abs(angle) > DX_PI_F / 2.0f)
	//{
	//	owner_.SetDirection(true);

	//	// 左向き(PI)を基準(0)に変換
	//	if (angle > 0) {
	//		angle -= DX_PI_F;
	//	}
	//	else {
	//		angle += DX_PI_F;
	//	}
	//}
	//else
	//{
	//	// 右向き状態
	//	owner_.SetDirection(false);
	//}

	// プレイヤーが左向きなら
	if(owner_.GetParameter()->direction)
	{
		// 角度を180度回転させる
		angle += UtilityCommon::Deg2RadF(180.0f);

		// 【修正】左向きの時は「反時計回り（-90度）」に回転
		// (x, y) -> (-y, x)
		float tempX = shotVec_.x;
		shotVec_.x = -shotVec_.y; // ここにマイナスがつきます
		shotVec_.y = tempX;
	}
	else
	{
		// 追加】時計回りに90度回転
		float tempX = shotVec_.x;
		shotVec_.x = shotVec_.y;
		shotVec_.y = -tempX;
	}
	owner_.SetShotVec(shotVec_);


	// =========================
	// モデル角度
	// =========================

	owner_.SetAngle(angle);

	// =========================
	// モデル角度
	// =========================

	owner_.SetAngle(angle);

	// =========================
	// チャージ
	// =========================

	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_AVILITY))
	{
		chageTime_ += 0.5f;
		shotTime_ += 0.1f;

		moveAmount_.x = std::sin(chageTime_);
		moveAmount_.y = 0.0f;

		owner_.SetMoveAmount(moveAmount_);
	}
	else
	{
		if (shotTime_ > 2.0f)
		{
			shotTime_ = 2.0f;
		}

		chageTime_ = 0.0f;

		// 自身のコライダーの判定を無効にする
		owner_.SetColliderActive(false);
		owner_.SetComponentActive("knockBack", false);
		owner_.SetComponentActive("jump", false);
		owner_.SetIsGround(false);

		// 攻撃判定用コライダーを有効にする
		attackCollider_->SetIsActive(true);


		isReflected_ = false;
		reflectCount_ = 4;

		currentState_ = "shot";
		currentStateFunction_ = stateFunctionMap_[currentState_];
	}
}

void ComponentAvilityChargeShot::ProcessMoveShot()
{

	shotTime_ -= 0.01f;



	if (shotTime_ <= 0.0f || reflectCount_ <= 0)
	{
		owner_.SetComponentActive("AvilityShot", true);

		if (gravityDir_ == ActorBase::DIR::RIGHT)
		{
			owner_.SetAngle(UtilityCommon::Deg2RadF(0.0f));
		}
		else if (gravityDir_ == ActorBase::DIR::LEFT)
		{
			owner_.SetAngle(UtilityCommon::Deg2RadF(90.0f));
		}
		else if (gravityDir_ == ActorBase::DIR::UP)
		{
			owner_.SetAngle(UtilityCommon::Deg2RadF(180.0f));
		}
		else if (gravityDir_ == ActorBase::DIR::DOWN)
		{
			owner_.SetAngle(UtilityCommon::Deg2RadF(0.0f));
		}


		// 自身のコライダーの判定を有効にする
		owner_.SetColliderActive(true);

		// ほとんど意味がなくノックバックするので無敵化を目指す
		owner_.SetComponentActive("knockBack", true);
		owner_.SetComponentActive("jump", true);

		// 攻撃判定用コライダーを無効にする
		attackCollider_->SetIsActive(false);

		currentState_ = "input";
		currentStateFunction_ = stateFunctionMap_[currentState_];
		return;
	}
	else
	{
		Vector2F dir = owner_.GetShotVec();

		moveAmount_.y = dir.y * shotTime_ * SHOT_SPEED;
		moveAmount_.x = dir.x * shotTime_ * SHOT_SPEED;

		// std::atan2(y, x) は右向きを0度（基準）として角度を返します。
		// 頭が上の素材を進行方向（右＝0度）に合わせるため、90度（PI / 2）引き算します。
		float currentAngle = std::atan2(dir.y, dir.x) - UtilityCommon::Deg2RadF(-90.0f);

		owner_.SetAngle(currentAngle);
	}


	// 各軸の衝突判定
	ProcessCollision(true);  // X軸
	ProcessCollision(false); // Y軸

	// 座標と移動量の更新
	owner_.SetMoveAmount(moveAmount_);
}

void ComponentAvilityChargeShot::ProcessCollision(bool isXAxis)
{
	float& moveVal = isXAxis ? moveAmount_.x : moveAmount_.y;

	if (moveVal == 0.0f) return;

	float& currentPos = isXAxis ? pos_.x : pos_.y;

	float sizeVal = isXAxis ? nowSize_.x : nowSize_.y;
	float otherSizeVal = isXAxis ? nowSize_.y : nowSize_.x;

	// =========================
	// 分割移動
	// =========================

	float move = moveVal;

	// タイル半分単位で分割すると安定
	float maxStep = 8.0f;

	int step = static_cast<int>(
		std::ceil(std::abs(move) / maxStep));

	if (step <= 0) step = 1;

	float stepMove = move / step;

	// =========================
	// 少しずつ移動
	// =========================

	for (int i = 0; i < step; i++)
	{
		currentPos += stepMove;

		bool isHit = false;
		ColliderArray::Result finalResult;

		// 判定点
		float margin = 0.45f;
		float offsets[] = { -margin, 0.0f, margin };

		for (float offset : offsets)
		{
			Vector2 checkPos = pos_.ToVector2();

			if (isXAxis)
			{
				// X軸移動時
				checkPos.x +=
					(stepMove > 0.0f)
					? sizeVal / 2.0f
					: -sizeVal / 2.0f;

				checkPos.y += otherSizeVal * offset;
			}
			else
			{
				// Y軸移動時
				checkPos.y +=
					(stepMove > 0.0f)
					? sizeVal / 2.0f
					: -sizeVal / 2.0f;

				checkPos.x += otherSizeVal * offset;
			}

			auto result =
				collisionManager_.IsHitStage(checkPos);

			//　衝突がない場合敵の衝突も試す
			if (!result.hit)
			{
				result =
					collisionManager_.IsHitStage(checkPos);
			}

			if (result.hit)
			{
				isHit = true;
				finalResult = result;
				break;
			}
		}

		// =========================
		// 衝突
		// =========================

		if (isHit)
		{
			// 1個戻す
			currentPos -= stepMove;

			CheckGroundStatus(stepMove, isXAxis);

			// =========================
			// 法線作成
			// =========================

			Vector2F normal(0.0f, 0.0f);

			if (isXAxis)
			{
				normal.x =
					(stepMove > 0.0f)
					? -1.0f
					: 1.0f;
			}
			else
			{
				normal.y =
					(stepMove > 0.0f)
					? -1.0f
					: 1.0f;
			}

			// =========================
			// 反射
			// =========================

			Vector2F reflectDir =
				UtilityCommon::Reflect(
					owner_.GetShotVec(),
					normal);

			owner_.SetShotVec(reflectDir);

			// =========================
			// 反射回数
			// =========================

			if (!isReflected_)
			{
				isReflected_ = true;

				reflectCount_--;

				if (shotTime_ > 0.5f)
				{
					shotTime_ -= 0.35f;
				}
			}

			// 移動停止
			moveVal = 0.0f;

			break;
		}
		else
		{
			isReflected_ = false;
		}
	}
}
void ComponentAvilityChargeShot::CheckGroundStatus(float moveVal, bool isXAxis)
{
	bool isGround = false;
	if (isXAxis)
	{
		if ((moveVal > 0.0f && gravityDir_ == ActorBase::DIR::RIGHT) ||
			(moveVal < 0.0f && gravityDir_ == ActorBase::DIR::LEFT)) isGround = true;
	}
	else
	{
		if ((moveVal > 0.0f && gravityDir_ == ActorBase::DIR::DOWN) ||
			(moveVal < 0.0f && gravityDir_ == ActorBase::DIR::UP)) isGround = true;
	}

	if (isGround) owner_.SetIsGround(true);
}