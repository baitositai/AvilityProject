#include <cassert>
#include "../../Factory/FactoryComponent.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Common/Camera.h"
#include "../OnHit/OnHitBase.h"
#include "../Collider/ColliderBase.h"
#include "../Parameter/ParameterActor.h"
#include "Common/Animation.h"
#include "ActorBase.h"

ActorBase::ActorBase(std::unique_ptr<ParameterActor> parameter, std::unique_ptr<Animation> animation) :
	parameter_(std::move(parameter)),
	animation_(std::move(animation)),
	scnMng_(SceneManager::GetInstance()),
	sndMng_(SoundManager::GetInstance()),
	resMng_(ResourceManager::GetInstance()),
	collMng_(CollisionManager::GetInstance()),
	facCom_(FactoryComponent::GetInstance())
{
	if (!parameter_) { parameter_ = std::make_unique<ParameterActor>(); }	// 必ず実態を持つ
	isActive_ = true;
	isDelete_ = false;
}

ActorBase::~ActorBase()
{

}

void ActorBase::Init()
{
	// コンポーネント生成
	CreateComponents();

	// コライダーの登録
	RegisterCollider();

	// アニメーション初期化
	InitAnimation();
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
	// 描画位置を設定
	Vector2F cameraPos = mainCamera.GetPos();
	parameter_->drawPos_ = Vector2::AddVector2(Vector2::AddVector2(parameter_->pos_.ToVector2(), parameter_->localPos_), cameraPos.ToVector2());

	// 描画
	DrawRotaGraph(
		parameter_->drawPos_.x,
		parameter_->drawPos_.y,
		parameter_->scale_,
		parameter_->angle_,
		parameter_->spriteTexture_[animation_->GetAnimationIndex()],
		parameter_->transparent_,
		parameter_->direction_
	);
}

void ActorBase::DebugDraw()
{
}

void ActorBase::InitAnimation()
{
}

void ActorBase::Delete()
{
	// コライダーがある場合削除
	if (collider_ != nullptr)
	{
		collider_->SetDelete();
	}
	// 削除
	isDelete_ = true;
}

void ActorBase::Landing()
{
	// 着地判定
	parameter_->isGround_ = true;
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
	collider_->SetDelete();
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
	// 必要なコンポーネントの生成
	for (const std::string& name : parameter_->componentkeys_)
	{
		AddComponent(name, std::move(facCom_.CreateComponent(name, *this)));
	}
}

void ActorBase::OnHit(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	if (onHit_ == nullptr) return;
	onHit_->Update(opponentCollider);
}