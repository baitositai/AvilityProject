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
#include "Common/Animation.h"
#include "ActorBase.h"

ActorBase::ActorBase(Parameter* parameter, const std::vector<std::string>& componentNameList, std::unique_ptr<Animation> animation) :
	DEFAULT_COMPONENT_CREATE_LIST(componentNameList),
	actorParameterPtr_(parameter),
	animation_(std::move(animation)),
	scnMng_(SceneManager::GetInstance()),
	sndMng_(SoundManager::GetInstance()),
	resMng_(ResourceManager::GetInstance()),
	collMng_(CollisionManager::GetInstance()),
	facCom_(FactoryComponent::GetInstance())
{
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
	actorParameterPtr_->drawPos = Vector2::AddVector2(Vector2::AddVector2(actorParameterPtr_->pos.ToVector2(), actorParameterPtr_->localPos), cameraPos.ToVector2());

	// 描画
	DrawRotaGraph(
		actorParameterPtr_->drawPos.x,
		actorParameterPtr_->drawPos.y,
		actorParameterPtr_->scale,
		actorParameterPtr_->angle,
		actorParameterPtr_->texuresHandle[animation_->GetAnimationIndex()],
		actorParameterPtr_->transparent,
		actorParameterPtr_->direction
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
	actorParameterPtr_->isGround = true;
}

void ActorBase::AddComponent(const std::string& name, std::unique_ptr<ComponentBase> component)
{
	// 同名のコンポーネントが既に存在するかチェック
	if (componentMap_.find(name) != componentMap_.end())
	{
		return; // 既に存在する場合は何もしない
	}

	// 実行順リストに追加（ここが所有権を持つ）
	// 後でポインタを Map に登録するため、一旦生のポインタを控える
	ComponentBase* ptr = component.get();
	componentList_.push_back(std::move(component));

	// 検索用マップに登録
	componentMap_.emplace(name, ptr);

	// 挿入に成功してるか確認
	//assert(result.second && "コンポーネントの追加に失敗しています");
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

void ActorBase::AddMoveAmount(const Vector2F moveAmount)
{
	if (actorParameterPtr_->moveAmount.x == 0.0f && actorParameterPtr_->moveAmount.y == 0.0f)
	{
		// 0ならリセット（上書き）
		actorParameterPtr_->moveAmount = moveAmount;
	}
	else
	{
		// 0以外なら加算
		actorParameterPtr_->moveAmount.x += moveAmount.x;
		actorParameterPtr_->moveAmount.y += moveAmount.y;
	}
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

const Vector2F ActorBase::GetGravityDirectionVector() const
{
	Vector2F dir = {};
	if (actorParameterPtr_->gravityDir == ActorBase::DIR::RIGHT) { dir = Vector2F(1.0f, 0.0f); }
	else if(actorParameterPtr_->gravityDir == ActorBase::DIR::LEFT) { dir = Vector2F(-1.0f, 0.0f); }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::UP) { dir = Vector2F(0.0f, -1.0f); }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::DOWN) { dir = Vector2F(0.0f, 1.0f); }
	return dir;
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
	for (const std::string& name : DEFAULT_COMPONENT_CREATE_LIST)
	{
		AddComponent(name, std::move(facCom_.CreateComponent(name, *this)));
	}
}

void ActorBase::OnHit(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	if (onHit_ == nullptr) return;
	onHit_->Update(opponentCollider);
}

const Vector2F ActorBase::GetFront() const
{
	Vector2F vec = {};

	// 重力方向に応じて前方向を返す
	if (actorParameterPtr_->gravityDir == ActorBase::DIR::RIGHT) { vec = { 0.0f, -1.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::LEFT) { vec = { 0.0f, 1.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::UP) { vec = { -1.0f, 0.0f }; }
	else { vec = { 1.0f, 0.0f }; }

	// キャラクターの向きで前方向を反転させる
	if (actorParameterPtr_->direction) { Vector2F::MulVector2FFloat(vec, -1.0f); }

	// 返す
	return vec;
}

const Vector2F ActorBase::GetBack() const
{
	Vector2F vec = {};

	// 重力方向に応じて後ろ方向を返す
	if (actorParameterPtr_->gravityDir == ActorBase::DIR::RIGHT) { vec = { 0.0f, 1.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::LEFT) { vec = { 0.0f, -1.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::UP) { vec = { 1.0f, 0.0f }; }
	else { vec = { -1.0f, 0.0f }; }

	// キャラクターの向きで後ろ方向を反転させる
	if (actorParameterPtr_->direction) { Vector2F::MulVector2FFloat(vec, -1.0f); }

	// 返す
	return vec;
}

const Vector2F ActorBase::GetUp() const
{
	Vector2F vec = {};
	
	// 重力方向に応じて上方向を返す
	if (actorParameterPtr_->gravityDir == ActorBase::DIR::RIGHT) { vec = { -1.0f, 0.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::LEFT) { vec = { 1.0f, 0.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::UP) { vec = { 0.0f, 1.0f }; }
	else { vec = { 0.0f, -1.0f }; }

	// 返す
	return vec;
}

const Vector2F ActorBase::GetDown() const
{
	Vector2F vec = {};
	
	// 重力方向に応じて下方向を返す
	if (actorParameterPtr_->gravityDir == ActorBase::DIR::RIGHT) { vec = { 1.0f, 0.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::LEFT) { vec = { -1.0f, 0.0f }; }
	else if (actorParameterPtr_->gravityDir == ActorBase::DIR::UP) { vec = { 0.0f, -1.0f }; }
	else { vec = { 0.0f, 1.0f }; }

	// 返す
	return vec;
}