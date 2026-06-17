#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../../OnHit/OnHitItemBase.h"
#include "../../Collider/ColliderBox.h"
#include "../../Object/Character/Player.h"
#include "ItemTreasure.h"

ItemTreasure::ItemTreasure(std::unique_ptr<ParameterItemTreasure> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemTreasure_ = dynamic_cast<ParameterItemTreasure*>(GetParameterItemPtr());
	assert(parameterItemTreasure_ != nullptr);

	// タグ定義
	tag_ = CollisionTags::TAG::ITEM_TREASURE;
	owner_ = nullptr;
	index_ = -1;
	ownerHeadPos_ = {};
}

ItemTreasure::~ItemTreasure()
{
}

void ItemTreasure::Init()
{
	// 衝突後処理
	onHit_ = std::make_unique<OnHitItemBase>(*this);

	// コライダー生成
	collider_ = std::make_shared<ColliderBox>(*this, tag_, parameterItemTreasure_->pos_, parameterItemTreasure_->hitSize_, parameterItemTreasure_->angle_);

	// 基底クラスの処理
	ActorBase::Init();
}

void ItemTreasure::Update()
{	
	// 移動量を初期化
	parameterItem_->moveAmount_ = {};
	
	if (owner_)
	{
		UpdateFollow();
	}

	// 基底クラスの処理
	ActorBase::Update();
}

void ItemTreasure::Draw()
{
	parameterItemTreasure_->drawPos_ = GetDrawPos();

	// 描画
	DrawRotaGraph(
		parameterItemTreasure_->drawPos_.x,
		parameterItemTreasure_->drawPos_.y,
		parameterItemTreasure_->scale_,
		parameterItemTreasure_->angle_,
		parameterItemTreasure_->texture_,
		parameterItemTreasure_->transparent_,
		parameterItemTreasure_->direction_
	);
}

void ItemTreasure::InitResource()
{
	// リソースに指定がない場合無視
	if (parameterItemTreasure_->resourceKey_ == "")
	{
		return;
	}

	// リソース取得
	parameterItemTreasure_->texture_ = resMng_.GetHandle(parameterItemTreasure_->resourceKey_);
}

void ItemTreasure::FollowPlayer(Player& player)
{
	// プレイヤー取得
	owner_ = &player;

	// 配列取得
	auto& treasureList = player.GetParameter().treasureList_;

	// 保持番号を取得
	index_ = treasureList.empty() ? 0 : static_cast<int>(treasureList.size());

	// プレイヤーに必要な情報を送る
	ParameterPlayer::TreasureStatus status = {};
	status.amount = parameterItemTreasure_->amount_;
	status.type = parameterItemTreasure_->type_;
	status.size = parameterItemTreasure_->hitSize_;
	treasureList.push_back(status);

	UpdateFollow();
}

void ItemTreasure::FollowRemove()
{	
	// 座標変更
	parameterItemTreasure_->pos_ = owner_->GetHeadPos(0);
	
	// 一部パラメータの初期化
	parameterItemTreasure_->gravityDir_ = ParameterActor::DIR::DOWN;
	parameterItemTreasure_->angle_ = 0.0f;

	// 吹き飛ばすためにランダムにノックバックパワーを設定
	parameterItemTreasure_->knockBackPower_ = {
		static_cast<float>(GetRand(200) + 200),
		static_cast<float>(GetRand(200) + 600),
	};
	
	// 追従解除
	owner_ = nullptr;
	ownerHeadPos_ = {};
}

void ItemTreasure::UpdateFollow()
{
	// 頭部位置取得
	ownerHeadPos_ = owner_->GetHeadPos(index_);

	// 重力や角度を所有者に合わせる
	const auto& ownerParameter = owner_->GetParameter();
	parameterItemTreasure_->gravityDir_ = ownerParameter.gravityDir_;
	parameterItemTreasure_->angle_ = ownerParameter.angle_;

	// 座標更新
	parameterItemTreasure_->pos_ = Vector2F::AddVector2F(parameterItemTreasure_->pos_, ownerHeadPos_);
}