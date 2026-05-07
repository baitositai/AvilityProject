#include <algorithm>
#include "../Utility/UtilityCommon.h"
#include "../Manager/Common/SceneManager.h"
#include "../Collider/ColliderBox.h"
#include "../OnHit/OnHitAvilityBox.h"
#include "../Common/Animation.h"
#include "AvilityBox.h"

AvilityBox::AvilityBox(const Parameter& parameter,const Vector2F& _placePos,const std::vector<std::string>& componentNameList) :
	parameter_(parameter),
	GimmickBase(&parameter_,componentNameList)
{
	//種類の設定
	gimmickType_ = TYPE::AVILITY_BOX;

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::AVILITY_BOX, parameter_.pos, parameter_.hitBoxSize, parameter_.angle);

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
	parameter_.pos = parameter_.placePos;
}

void AvilityBox::Update(void)
{
	PushResult();
	parameter_.moveAmount = Vector2F();
	isPushPlayer_ = false;
	GimmickBase::Update();

	//if (blastWaitCnt_ > 0.0f)
	//{
	//	blastWaitCnt_ -= scnMng_.GetDeltaTime();
	//}
	//else
	//{
	//	collider_->SetDelete();
	//	return;
	//}

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
	if (parameter_.boxNum == 1) { color = UtilityCommon::GREEN; }
	else if (parameter_.boxNum == 2) { color = UtilityCommon::BLUE; }

	DrawCircle(parameter_.pos.x, parameter_.pos.y,10, color);

	//プレイヤーが押し出している最中のみ描画
	if(isPushPlayer_){ DrawCircle(parameter_.pos.x, parameter_.pos.y, 3, UtilityCommon::CYAN); }


	Vector2F dirPos = Vector2F();
	constexpr float LOCAL = 15.0f;
	parameter_.direction ? dirPos.x = -LOCAL : dirPos.x = LOCAL;
	DrawCircle(parameter_.pos.x + dirPos.x, parameter_.pos.y, 3, UtilityCommon::LIME);


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
	for (auto& info : hitInfo_)
	{
		Vector2F push = {};

		//X方向押し出し
		//if (info.overlapX < info.overlapY)
		{
			push.x = -(info.overlapX + 0.01f) * info.signX;
		}
		//else
		{
			push.y = -(info.overlapY + 0.01f) * info.signY;
		}

		totalPush = Vector2F::AddVector2F(totalPush, push);
	}

	parameter_.pos = Vector2F::AddVector2F(parameter_.pos, totalPush);

	//処理し終わったら破棄
	hitInfo_.clear();
}
