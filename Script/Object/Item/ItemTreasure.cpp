#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../../OnHit/OnHitItemTreasure.h"
#include "../../Collider/ColliderBox.h"
#include "../../Object/Character/Player.h"
#include "../../Render/PixelRenderer.h"
#include "../../Render/PixelMaterial.h"
#include "../../Utility/UtilityCommon.h"
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
	preGravityDir_ = ParameterActor::DIR::MAX;
}

ItemTreasure::~ItemTreasure()
{
}

void ItemTreasure::Init()
{
	// 衝突後処理
	onHit_ = std::make_unique<OnHitItemTreasure>(*this);

	// コライダー生成
	collider_ = std::make_shared<ColliderBox>(*this, tag_, parameterItemTreasure_->pos_, parameterItemTreasure_->hitSize_, parameterItemTreasure_->angle_);

	// 基底クラスの処理
	ActorBase::Init();

	// 持ち越ししている場合
	if (isCarryOver_)
	{
		collider_->SetIsActive(false);
	}
}

void ItemTreasure::Update()
{	
	// 移動量を初期化
	parameterItemTreasure_->moveAmount_ = {};
	
	if (owner_)
	{
		UpdateFollow();
	}

	// 基底クラスの処理
	ActorBase::Update();
}

void ItemTreasure::Draw()
{	
	// 描画しない場合は無視
	if (!isDraw_) return;
		
	// 描画位置を取得
	parameterItemTreasure_->drawPos_ = GetDrawCenterPos();

	// 描画サイズを現在のスケールに合わせる
	Vector2F nowSize = Vector2F::MulVector2FFloat(parameterItemTreasure_->drawSize_.ToVector2F(), parameterItemTreasure_->scale_);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameterItemTreasure_->drawPos_, nowSize.ToVector2());

	// X軸の反転
	float isReverseX = parameterItemTreasure_->direction_ ? 1.0f : 0.0f;

	// 定数バッファの更新
	material_->SetConstBuf(0, FLOAT4{ parameterItemTreasure_->color_.x,parameterItemTreasure_->color_.y ,parameterItemTreasure_->color_.z, parameterItemTreasure_->alpha_ });
	material_->SetConstBuf(1, FLOAT4{ isReverseX, 0.0f, parameterItemTreasure_->scale_, parameterItemTreasure_->angle_ });

	// 描画処理
	renderer_->Draw();
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

	// プレイヤー側にも登録
	player.AttachedItem(this);

	// 配列取得
	auto& treasureList = player.GetParameter().treasureList_;

	// 保持番号を取得
	index_ = treasureList.empty() ? 0 : static_cast<int>(treasureList.size());

	// 重力方向のバックアップ取得
	preGravityDir_ = player.GetParameter().gravityDir_;

	// プレイヤーに必要な情報を送る
	ParameterPlayer::TreasureStatus status = {};
	status.amount = parameterItemTreasure_->amount_;
	status.type = parameterItemTreasure_->type_;
	status.size = parameterItemTreasure_->hitSize_;
	treasureList.push_back(status);

	// コンポーネント無効
	SetComponentActive("gravity", false);
	SetComponentActive("move", false);

	// コライダー無効
	collider_->SetIsActive(false);

	// 持っている間は持ち越しする
	isCarryOver_ = true;

	// 初期更新
	UpdateFollow();
}

void ItemTreasure::FollowRemove()
{	
	// 座標変更
	parameterItemTreasure_->pos_ = Vector2F::AddVector2F(owner_->GetParameter().pos_, owner_->GetHeadLocalPos(0));
	
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

	// コンポーネント有効
	SetComponentActive("gravity", true);
	SetComponentActive("move", true);

	// コライダー有効
	collider_->SetIsActive(true);

	// 持ち越し解除
	isCarryOver_ = false;
}

void ItemTreasure::UpdateFollow()
{
	const auto& ownerParameter = owner_->GetParameter();

	// 所有者のパラメータに合わせる
	parameterItemTreasure_->gravityDir_ = ownerParameter.gravityDir_;
	if (preGravityDir_ != parameterItemTreasure_->gravityDir_) { parameterItemTreasure_->angle_ = ownerParameter.angle_; }
	
	// 1. プレイヤーの足元からの「頭部のローカル位置」を取得
	Vector2F ownerHeadLocalPos = owner_->GetHeadLocalPos(index_);

	// 2. 宝箱のハーフサイズの取得
	Vector2F halfSize = Vector2F::MulVector2FFloat(parameterItemTreasure_->hitSize_.ToVector2F(), 0.5f);

	// 3. ローカル空間上で、頭部位置からさらに宝箱のサイズ分だけ上にズラす（ローカル同士の計算）
	Vector2F totalLocalOffset;
	totalLocalOffset.x = ownerHeadLocalPos.x;
	totalLocalOffset.y = ownerHeadLocalPos.y - halfSize.y;

	// 4. 合成したローカルオフセットを、現在の重力方向のワールドベクトルに変換
	Vector2F worldOffset = UtilityCommon::ConvertLocalToWorldByGravity(totalLocalOffset, parameterItemTreasure_->gravityDir_);

	parameterItemTreasure_->pos_.x = ownerParameter.pos_.x + worldOffset.x;
	parameterItemTreasure_->pos_.y = ownerParameter.pos_.y + worldOffset.y;

	// 重力バックアップ
	preGravityDir_ = parameterItemTreasure_->gravityDir_;

	collider_->SetIsActive(false);
}

void ItemTreasure::InitDraw()
{
	// リソースの取得と同時に必要な情報を取得
	parameterItemTreasure_->drawSize_ = parameterItemTreasure_->hitSize_;
	parameterItemTreasure_->drawHalfSize_ = Vector2(parameterItemTreasure_->drawSize_.x / 2, parameterItemTreasure_->drawSize_.y / 2);

	// X軸の反転
	float isReverseX = parameterItemTreasure_->direction_ ? 1.0f : 0.0f;

	// 基底クラスではスプライト画像を前提で用意
	// マテリアルの生成
	material_ = std::make_unique<PixelMaterial>(resMng_.GetHandle("standardTexture"), CONST_BUFFER_SIZE);
	material_->AddTextureBuf(parameterItemTreasure_->texture_);
	material_->AddConstBuf(FLOAT4{ parameterItemTreasure_->color_.x, parameterItemTreasure_->color_.y,parameterItemTreasure_->color_.z, parameterItemTreasure_->alpha_ });
	material_->AddConstBuf(FLOAT4{ isReverseX, 0.0f, parameterItemTreasure_->scale_, parameterItemTreasure_->angle_ });

	// レンダラーの生成
	renderer_ = std::make_unique<PixelRenderer>(*material_);

	// 中心位置に設定
	parameterItemTreasure_->drawPos_ = GetDrawCenterPos();

	// 描画サイズを現在のスケールに合わせる
	Vector2F nowSize = Vector2F::MulVector2FFloat(parameterItemTreasure_->drawSize_.ToVector2F(), parameterItemTreasure_->scale_);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameterItemTreasure_->drawPos_, nowSize.ToVector2());
}