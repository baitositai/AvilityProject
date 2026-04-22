#include "../../Factory/FactoryComponent.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Common/Camera.h"
#include "../OnHit/OnHitBase.h"
#include "../Collider/ColliderBase.h"
#include "ActorBase.h"

ActorBase::ActorBase(Parameter* parameter, const std::vector<std::string>& componentNameList) :
	DEFAULT_COMPONENT_CREATE_LIST(componentNameList),
	actorParameterPtr_(parameter),
	scnMng_(SceneManager::GetInstance()),
	sndMng_(SoundManager::GetInstance()),
	resMng_(ResourceManager::GetInstance()),
	collMng_(CollisionManager::GetInstance())
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
	if (componentMap_.empty()) return;

	for (const auto& componet : componentMap_)
	{
		if (componet.second == nullptr) continue;

		componet.second->Update();
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
		actorParameterPtr_->texuresHandle[parameterAnimation_.animationIndex],
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

void ActorBase::AddComponent(const std::string& name, std::unique_ptr<ComponentBase> component)
{
	// 同名のコンポーネントが既に存在するか確認しながら挿入
	auto result = componentMap_.try_emplace(name, std::move(component));

	// 挿入に失敗した場合
	if (!result.second)
	{
		// 文字列を作成してデバッグ出力に送る
		std::string errorMessage = "Warning: Component [" + name + "] already exists.\n";
		OutputDebugStringA(errorMessage.c_str());
	}
}

void ActorBase::RemoveComponent(const std::string& name)
{
	// 指定された名前の要素を検索する
	auto it = componentMap_.find(name);

	// 要素が見つかった場合は削除する
	if (it != componentMap_.end())
	{
		componentMap_.erase(it);
	}
}


void ActorBase::SetAnimationParameter(const int animationStartIndex, const int animationFinishIndex, const float animationSpeed, const bool isLoop)
{
	parameterAnimation_.animationStartIndex = animationStartIndex;
	parameterAnimation_.animationFinishIndex = animationFinishIndex;
	parameterAnimation_.animationSpeed = animationSpeed;
	parameterAnimation_.isLoop = isLoop;
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
	std::unique_ptr<FactoryComponent> factoryComponent = std::make_unique<FactoryComponent>();
	for (const std::string& name : DEFAULT_COMPONENT_CREATE_LIST)
	{
		AddComponent(name, std::move(factoryComponent->CreateComponent(name, *this)));
	}
}

void ActorBase::OnHit(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	if (onHit_ == nullptr) return;
	onHit_->Update(opponentCollider);
}