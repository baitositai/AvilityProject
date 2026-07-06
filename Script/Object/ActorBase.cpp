#include <cassert>
#include "../../Factory/FactoryComponent.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/UiManager.h"
#include "../../Resource/ResourceTexture.h"
#include "../../Render/PixelMaterial.h"
#include "../../Render/PixelRenderer.h"
#include "../OnHit/OnHitBase.h"
#include "../Collider/ColliderBase.h"
#include "../Parameter/ParameterActor.h"
#include "Common/Animation.h"
#include "ActorBase.h"

ActorBase::ActorBase(std::unique_ptr<ParameterActor> parameter) :
	parameter_(std::move(parameter)),
	scnMng_(SceneManager::GetInstance()),
	sndMng_(SoundManager::GetInstance()),
	resMng_(ResourceManager::GetInstance()),
	collMng_(CollisionManager::GetInstance()),
	facCom_(FactoryComponent::GetInstance()),
	uiMng_(UiManager::GetInstance())
{
	if (!parameter_) { parameter_ = std::make_unique<ParameterActor>(); }	// 必ず実態を持つ
	isActive_ = true;
	isDelete_ = false;
	isDraw_ = true;
}

ActorBase::~ActorBase()
{

}

void ActorBase::Init()
{	
	// アニメーション初期化
	InitAnimation();

	// リソースの初期化
	InitResource();

	// UIの初期化
	InitUi();

	// 描画関係の初期化
	InitDraw();
	
	// コンポーネント生成
	CreateComponents();

	// コライダーの登録
	RegisterCollider();
}

void ActorBase::Update()
{
	if (componentList_.empty()) return;

	for (auto& component : componentList_)
	{
		// unique_ptrが有効かチェック
		if (component)
		{
			if (component->IsActive())
			{
				component->Update();
			}
		}
		else
		{
			OutputDebugString(L"エラー: componentList_ の中に nullptr が存在します\n");
		}
	}
}

void ActorBase::Draw()
{	
	// 描画しない場合は無視
	if (!isDraw_) return;
	
	// 中心位置に設定
	parameter_->drawPos_ = GetDrawCenterPos();

	// 描画サイズを現在のスケールに合わせる
	Vector2F nowSize = Vector2F::MulVector2FFloat(parameter_->drawSize_.ToVector2F(), parameter_->scale_);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameter_->drawPos_, nowSize.ToVector2());

	// X軸の反転
	float isReverseX = parameter_->direction_ ? 1.0f : 0.0f;

	// 定数バッファの更新
	material_->SetConstBuf(0, FLOAT4{ parameter_->color_.x,parameter_->color_.y ,parameter_->color_.z, parameter_->alpha_ });
	material_->SetConstBuf(1, FLOAT4{ isReverseX, 0.0f, parameter_->scale_, parameter_->angle_ });
	material_->SetConstBuf(2, FLOAT4{ (float)parameter_->divisionNum_.x, (float)parameter_->divisionNum_.y , parameter_->drawIndex_, 0.0f });
	
	// 描画処理
	renderer_->Draw();
}

void ActorBase::DebugDraw()
{
}

void ActorBase::InitAnimation()
{
	// パラメーターにアニメーション情報が空の場合
	if (parameter_->animationDataMap_.empty())
	{
		// 中身を空にしとく
		animation_ = nullptr;

		// 終了
		return;
	}

	// アニメーション生成
	animation_ = std::make_unique<Animation>();

	// アニメーション情報の格納
	for (auto& animation : parameter_->animationDataMap_)
	{
		Animation::Data& animatioData = animation.second;
		animation_->Add(animation.first, animatioData.startIndex, animatioData.endIndex, animatioData.animationSpeed);
	}
}

void ActorBase::InitResource()
{	
	// リソースに指定がない場合無視
	if (parameter_->resourceKey_ == "") 
	{
		return;
	}

	// リソース取得
	parameter_->texture_ = resMng_.GetHandle(parameter_->resourceKey_);
}

void ActorBase::InitDraw()
{
	// リソースの取得と同時に必要な情報を取得
	const auto texture = resMng_.GetResourceTexture(parameter_->resourceKey_);
	parameter_->drawSize_ = texture->GetSize();
	parameter_->divisionNum_ = texture->GetDivsion();
	parameter_->drawHalfSize_ = Vector2(parameter_->drawSize_.x / 2, parameter_->drawSize_.y / 2);

	// X軸の反転
	float isReverseX = parameter_->direction_ ? 1.0f : 0.0f;

	// 基底クラスではスプライト画像を前提で用意
	// マテリアルの生成
	material_ = std::make_unique<PixelMaterial>(resMng_.GetHandle("standardSprite"), DEFAULT_CONST_BUFFER_SIZE);
	material_->AddTextureBuf(parameter_->texture_);
	material_->AddConstBuf(FLOAT4{ parameter_->color_.x, parameter_->color_.y,parameter_->color_.z, parameter_->alpha_ });
	material_->AddConstBuf(FLOAT4{ isReverseX, 0.0f, parameter_->scale_, parameter_->angle_ });
	material_->AddConstBuf(FLOAT4{ (float)parameter_->divisionNum_.x, (float)parameter_->divisionNum_.y, parameter_->drawIndex_, 0.0f });

	// レンダラーの生成
	renderer_ = std::make_unique<PixelRenderer>(*material_);

	// 中心位置に設定
	parameter_->drawPos_ = GetDrawCenterPos();

	// 描画サイズを現在のスケールに合わせる
	Vector2F nowSize = Vector2F::MulVector2FFloat(parameter_->drawSize_.ToVector2F(), parameter_->scale_);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameter_->drawPos_, nowSize.ToVector2());
}

void ActorBase::InitUi()
{
}

void ActorBase::Delete()
{
	// コンポーネントの取り外し処理
	for (auto& component : componentList_)
	{
		component->Remove();
	}
	componentList_.clear();
	componentMap_.clear();

	// コライダーがある場合削除
	if (collider_ != nullptr)
	{
		collider_->Delete();
		collider_ = nullptr;
	}
	// 削除
	isDelete_ = true;
}

void ActorBase::Landing()
{
	// 着地判定
	parameter_->isGround_ = true;
}

void ActorBase::Damage(const int damage, const Vector2& hitPos)
{
	parameter_->hp_ -= damage;
	if (0 > parameter_->hp_)
	{
		parameter_->hp_ = 0;
	}
}

void ActorBase::AddComponent(const std::string& name, std::unique_ptr<ComponentBase> component)
{
	// 同名のコンポーネントが既に存在するかチェック
	if (componentMap_.find(name) != componentMap_.end())
	{
		return; // 既に存在する場合は何もしない
	}

	// 実行順リストに追加
	ComponentBase* ptr = component.get();
	componentList_.push_back(std::move(component));

	// 検索用マップに登録
	componentMap_.emplace(name, ptr);

}

void ActorBase::RemoveComponent(const std::string& name)
{
	auto it = componentMap_.find(name);
	if (it != componentMap_.end())
	{
		// 1. vector側から実体を削除する
		// mapに保存していたポインタ(it->second)を使って検索
		auto listIt = std::find_if(componentList_.begin(), componentList_.end(),
			[target = it->second](const std::unique_ptr<ComponentBase>& comp) {
				return comp.get() == target;
			});

		if (listIt != componentList_.end())
		{
			componentList_.erase(listIt);
		}

		// 2. map側から登録を削除する
		componentMap_.erase(it);
	}
}

void ActorBase::SetColliderActive(const bool isActive)
{
	if (collider_ != nullptr)
	{
		collider_->SetIsActive(isActive);
	}
}

const float ActorBase::GetGravityPowerWithBoost() const
{
	float boostGravityPower = parameter_->gravityPower_ * (1.0f + parameter_->gravityBoostRate_);
	return boostGravityPower;
}

bool ActorBase::IsComponentActive(const std::string& name) const
{
	auto it = componentMap_.find(name);
	if (it != componentMap_.end())
	{
		return it->second->IsActive();
	}
	return false; // 見つからない場合は基本 false
}

void ActorBase::SetComponentActive(const std::string& name, const bool isActive)
{
	auto it = componentMap_.find(name);
	if (it != componentMap_.end())
	{
		it->second->SetActive(isActive);
	}
}

void ActorBase::SetIsDelete(void)
{
	isActive_ = false;
	isDelete_ = true;

	//当たり判定の消去
	collider_->Delete();
}

void ActorBase::RegisterCollider()
{
	// 空の場合無視
	if (collider_ == nullptr)
	{
		return;
	}

	// 登録
	collMng_.Add(collider_);
}

void ActorBase::CreateComponents()
{
	if (!componentList_.empty())
	{
		// 実体を持っている list 側からループを回して Remove を呼ぶ
		for (const auto& component : componentList_)
		{
			if (component)
			{
				component->Remove();
			}
		}

		// 参照・実体をそれぞれクリアして完全に解放する
		componentMap_.clear();
		componentList_.clear();
	}

	for (const std::string& name : parameter_->componentkeys_)
	{
		auto component = facCom_.CreateComponent(name, *this);
		component->Create();
		AddComponent(name, std::move(component));
	}
}

const Vector2 ActorBase::GetDrawCenterPos() const
{
	// カメラ位置分オフセット
	Vector2F cameraPos = mainCamera.GetPos();
	Vector2 drawPos = Vector2::AddVector2(Vector2::AddVector2(parameter_->pos_.ToVector2(), parameter_->localPos_), cameraPos.ToVector2());

	// 描画サイズの半分位置を位置をずらす
	return Vector2::SubVector2(drawPos, parameter_->drawHalfSize_);
}

void ActorBase::OnHit(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	if (onHit_ == nullptr) return;
	onHit_->Update(opponentCollider);
}

const int ActorBase::GetAttackPowerWithBoost() const
{
	float boostAttackPower = static_cast<float>(parameter_->attackPower_) * (1.0f + parameter_->attackBoostRate_);
	return static_cast<int>(boostAttackPower);
}