#include <algorithm>
#include "../Utility/UtilityCommon.h"
#include "../Manager/Common/SceneManager.h"
#include "../Collider/ColliderBox.h"
#include "../OnHit/OnHitAvilityBox.h"
#include "../Common/Animation.h"
#include "AvilityBox.h"

AvilityBox::AvilityBox(std::unique_ptr<ParameterAvilityBox> parameter, CharacterBase& owner) :
	owner_(owner),
	GimmickBase(std::move(parameter))
{	
	// 箱用のパラメータ
	parameterAvilityBox_ = dynamic_cast<ParameterAvilityBox*>(GetParameterGimmickPtr());
	assert(parameterAvilityBox_ != nullptr);

	//種類の設定
	gimmickType_ = TYPE::AVILITY_BOX;

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::AVILITY_BOX, parameterAvilityBox_->pos_, parameterAvilityBox_->hitSize_, parameterAvilityBox_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitAvilityBox>(*this);
}

AvilityBox::~AvilityBox()
{
}

void AvilityBox::Init(void)
{
	GimmickBase::Init();

	//座標をプレイヤーとローカル座標分離れている座標にする
	parameterAvilityBox_->pos_ = parameterAvilityBox_->placePos_;
}

void AvilityBox::Update(void)
{
	//PushResult();
	if (!Vector2F::IsSameVector2F(onHit_->GetMoveAmount(), Vector2F()))
	{
		int i = 0;
	}
	parameterAvilityBox_->moveAmount_ = onHit_->GetMoveAmount();
	onHit_->ResetMoveAmount();
	isHitWall_ = false;
	GimmickBase::Update();

}

void AvilityBox::Draw(void)
{
	GimmickBase::Draw();
}

void AvilityBox::DebugDraw(void)
{
	if (collider_ == nullptr) return;
	collider_->DebugDraw();

	unsigned int color = UtilityCommon::RED;
	if (parameterAvilityBox_->boxNum_ == 1) { color = UtilityCommon::GREEN; }
	else if (parameterAvilityBox_->boxNum_ == 2) { color = UtilityCommon::BLUE; }

	DrawCircle(parameterAvilityBox_->pos_.x, parameterAvilityBox_->pos_.y,10, color);

	//プレイヤーが押し出している最中のみ描画
	if(isPushPlayer_){ DrawCircle(parameterAvilityBox_->pos_.x, parameterAvilityBox_->pos_.y, 3, UtilityCommon::CYAN); }


	Vector2F dirPos = Vector2F();
	constexpr float LOCAL = 15.0f;
	parameterAvilityBox_->direction_ ? dirPos.x = -LOCAL : dirPos.x = LOCAL;
	DrawCircle(parameterAvilityBox_->pos_.x + dirPos.x, parameterAvilityBox_->pos_.y, 3, UtilityCommon::LIME);
}

void AvilityBox::AddHitInfo(const HitInfo& _hitInfo)
{
	hitInfo_.push_back(_hitInfo);
}

void AvilityBox::PushResult(void)
{
	if (hitInfo_.empty())return;

	std::sort(hitInfo_.begin(), hitInfo_.end(),
		[](const HitInfo& a, const HitInfo& b)
		{
			//優先度の値が低い順に並べる
			return a.priority < b.priority;
		});
	Vector2F totalPush = {};
	Vector2F moveAmount = {};
	Vector2F prevPos = parameterAvilityBox_->pos_;

	for (auto& info : hitInfo_)
	{
		Vector2F push = {};
		Vector2F prevPos = parameterAvilityBox_->pos_;
		//X方向押し出し
		//if (info.overlapX < info.overlapY)
		{
			push.x = -(info.overlapX + 0.01f) * info.signX;
		}
		//else
		{
			push.y = (info.overlapY + 0.01f) * info.signY;
		}

		totalPush = Vector2F::AddVector2F(totalPush, push);
		parameterAvilityBox_->moveAmount_ = Vector2F::SubVector2F(parameterAvilityBox_->pos_, prevPos);
	}

	parameterAvilityBox_->pos_ = Vector2F::AddVector2F(parameterAvilityBox_->pos_, totalPush);

	//処理し終わったら破棄
	hitInfo_.clear();
}
