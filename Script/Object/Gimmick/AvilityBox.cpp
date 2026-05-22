#include <algorithm>
#include "../Utility/UtilityCommon.h"
#include "../Manager/Common/SceneManager.h"
#include "../Collider/ColliderBox.h"
#include "../Object/ActorBase.h"
#include "../Object/Character/CharacterBase.h"
#include "../OnHit/OnHitAvilityBox.h"
#include "../Common/Animation.h"
#include "AvilityBox.h"

#include "../Component/ComponentMove.h"

AvilityBox::AvilityBox( std::unique_ptr<ParameterActor> parameter, CharacterBase& owner)
	: GimmickBase(std::move(parameter)) // 親クラス（GimmickBase）のコンストラクタに所有権を渡す
	, owner_(owner)
	, isPushPlayer_(false)
	, isHitWall_(false)
	, blastWaitCnt_(0.0f)
{
	//種類の設定
	gimmickType_ = TYPE::AVILITY_BOX;

	auto& param = GetParameter();

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::AVILITY_BOX
		, param.pos_, param.hitSize_, param.angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitAvilityBox>(*this);
}

AvilityBox::~AvilityBox()
{
}

void AvilityBox::Init(void)
{
	GimmickBase::Init();
	auto& param = GetParameter();

	//座標をプレイヤーとローカル座標分離れている座標にする
	// プレイヤーのパラメータ
	// 位置の決定
	{
		// ローカル座標をJsonで読み込み、プレイヤーの向きによって設置場所を変える
		Vector2F localPos = { 50.0f, 0.0f };
		const bool charaDir = owner_.GetParameter().direction_;
		const Vector2F& charaPos = owner_.GetParameter().pos_;

		// ポインタ経由（->）でのアクセスに変更
		param.pos_ = charaDir ? Vector2F::SubVector2F(charaPos, localPos) : Vector2F::AddVector2F(charaPos, localPos);
	}

	// コンポーネントの初期化
	componentList_.emplace_back(std::make_unique<ComponentMove>(*this));

}

void AvilityBox::Update(void)
{
	auto& param = GetParameter();

	// 衝突フラグの初期化（毎フレーム、衝突判定の前にリセット）
	isHitWall_ = false;
	isPushPlayer_ = false;

	// 移動後の値を初期化
	param.moveAmount_ = {};

	//// 状態別処理
	//UpdateComponentState();

	//// アビリティ処理
	//UpdateComponentAvility();

	// 基底クラスの処理
	ActorBase::Update();

	// 溜まった衝突情報から最終的な位置を決定し、移動量を確定させる
	PushResult();
}

void AvilityBox::Draw(void)
{
	//GimmickBase::Draw();
}

void AvilityBox::DebugDraw(void)
{
	auto& param = GetParameter();

	if (collider_ == nullptr) return;
	collider_->DebugDraw();

	// --- ここから四角形の描画処理を追加 ---
	// 1. ボックスの「中心座標」と「サイズ」を取得
	float centerX = param.pos_.x;
	float centerY = param.pos_.y;
	float width = param.hitSize_.x;
	float height = param.hitSize_.y;

	// 2. 中心から「左上(TopLeft)」と「右下(BottomRight)」の座標を計算
	int left = static_cast<int>(centerX - width / 2.0f);
	int top = static_cast<int>(centerY - height / 2.0f);
	int right = static_cast<int>(centerX + width / 2.0f);
	int bottom = static_cast<int>(centerY + height / 2.0f);

	// 3. 色を決める（プレイヤー押し出し中なら水色、それ以外は赤）
	unsigned int boxColor = isPushPlayer_ ? UtilityCommon::CYAN : UtilityCommon::RED;

	// 4. 四角形の枠線を描画 (最後の引数「FALSE」で塗りつぶしなしの枠線になります)
	DrawBox(left, top, right, bottom, boxColor, FALSE);



	if (collider_ == nullptr) return;
	collider_->DebugDraw();

	unsigned int color = UtilityCommon::RED;
	/*if (parameterAvilityBox_->boxNum_ == 1) { color = UtilityCommon::GREEN; }
	else if (parameterAvilityBox_->boxNum_ == 2) { color = UtilityCommon::BLUE; }*/

	DrawCircle(param.pos_.x, param.pos_.y,10, color);

	//プレイヤーが押し出している最中のみ描画
	if(isPushPlayer_){ DrawCircle(param.pos_.x, param.pos_.y, 3, UtilityCommon::CYAN); }


	Vector2F dirPos = Vector2F();
	constexpr float LOCAL = 15.0f;
	param.direction_ ? dirPos.x = -LOCAL : dirPos.x = LOCAL;
	DrawCircle(param.pos_.x + dirPos.x, param.pos_.y, 3, UtilityCommon::LIME);

	//情報の描画
	DrawFormatString(param.pos_.x, param.pos_.y, UtilityCommon::GRAY, L"overlapX: %.2f", hitInfo_.empty() ? 0.0f : hitInfo_.front().overlapX);
}

void AvilityBox::AddHitInfo(const HitInfo& _hitInfo)
{
	hitInfo_.push_back(_hitInfo);
}

void AvilityBox::PushResult(void)
{
	if (hitInfo_.empty()) return;
	auto& param = GetParameter();

	// 変更：プレイヤーからの移動(1)を先に処理し、ステージ(0)を最後に処理するため、
	// 優先度の値が「大きい順（降順）」にソートします。
	std::sort(hitInfo_.begin(), hitInfo_.end(),
		[](const HitInfo& a, const HitInfo& b)
		{
			return a.priority > b.priority;
		});

	Vector2F startPos = param.pos_; // 処理前の座標を保持

	for (const auto& info : hitInfo_)
	{
		// 優先度1 or 2：プレイヤーや他のボックスからの押し出し（移動の適用）
		if (info.priority == 1 || info.priority == 2)
		{
			// 相手の移動量を自分の座標に加算（まずは一緒に動かす）
			param.pos_ = Vector2F::AddVector2F(param.pos_, info.moveAmount);

			// お互いのめり込みを分離する微調整
			if (info.overlapX < info.overlapY)
			{
				param.pos_.x -= (info.overlapX + 0.01f) * info.signX;
			}
			else
			{
				param.pos_.y -= (info.overlapY + 0.01f) * info.signY;
			}
		}
		// 優先度0：ステージ（壁・床）からの押し戻し（最終確定ガード）
		else if (info.priority == 0)
		{
			// X方向（横壁）のめり込みがある場合
			if (info.overlapX > 0.0f)
			{
				param.pos_.x -= (info.overlapX + 0.01f) * info.signX;
			}

			// Y方向（床・天井）のめり込みがある場合
			if (info.overlapY > 0.0f)
			{
				param.pos_.y -= (info.overlapY + 0.01f) * info.signY;
			}
		}
	}

	// 最終的にこのフレームで動いた総量を moveAmount_ に確定させる
	param.moveAmount_ = Vector2F::SubVector2F(param.pos_, startPos);

	// 処理し終わったら破棄
	hitInfo_.clear();
}