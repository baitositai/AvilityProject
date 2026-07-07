#include "../Manager/Common/SceneManager.h"
#include "../../Parameter/Gimmick/ParameterGimmick.h"
#include "../../OnHit/OnHitDropRock.h"
#include "../Collider/ColliderCircle.h"
#include "GimmickDropRock.h"

GimmickDropRock::GimmickDropRock(std::unique_ptr<ParameterGimmick> parameter):
	GimmickBase(std::move(parameter)),
	state_(STATE::NONE),
	parameterDropRock_(),
	hitRadius_(ROCK_SIZE)
{
	// パラメータ情報
	parameterDropRock_ = dynamic_cast<ParameterGimmick*>(GetParameterGimmickPtr());
	assert(parameterDropRock_ != nullptr);
}

GimmickDropRock::~GimmickDropRock()
{
}

void GimmickDropRock::CreateRock(const Vector2F _createPos)
{
	parameterDropRock_->pos_ = _createPos;
	parameterDropRock_->hitSize_ = Vector2(ROCK_SIZE, ROCK_SIZE);
	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::DROP_ROCK, parameterDropRock_->pos_, hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitDropRock>(*this);

	// 初期化
	ActorBase::Init();
}

void GimmickDropRock::Init()
{
	parameterDropRock_->hitSize_ = Vector2(ROCK_SIZE, ROCK_SIZE);

	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::DROP_ROCK, parameterDropRock_->pos_, hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitDropRock>(*this);

	// 初期化
	ActorBase::Init();

	waitCnt_ = 0.0f;
	update_ = std::bind(&GimmickDropRock::UpdateWait, this);
}

void GimmickDropRock::Update()
{
	update_();

	// 基底クラスの処理
	ActorBase::Update();
}

void GimmickDropRock::Draw()
{
	collider_->DebugDraw();
}

void GimmickDropRock::ChangeCreate(void)
{
}

void GimmickDropRock::UpdateWait(void)
{
	if (waitCnt_ > WAIT_TIME)
	{
		update_ = std::bind(&GimmickDropRock::UpdateDrop, this);
	}
	// コンポーネント無効
	SetComponentActive("gravity", false);
	SetComponentActive("move", false);
	waitCnt_ += scnMng_.GetDeltaTime();
}

void GimmickDropRock::UpdateDrop(void)
{
	// コンポーネント有効
	SetComponentActive("gravity", true);
	SetComponentActive("move", true);
}
