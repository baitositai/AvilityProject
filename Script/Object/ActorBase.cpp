#include "../../Factory/FactoryComponent.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "ActorBase.h"

ActorBase::ActorBase(Parameter* parameter, const std::vector<std::string>& componentNameList) :
	DEFAULT_COMPONENT_CREATE_LIST(componentNameList),
	actorParameterPtr_(parameter),
	scnMng_(SceneManager::GetInstance()),
	sndMng_(SoundManager::GetInstance()),
	resMng_(ResourceManager::GetInstance())
{
}

ActorBase::~ActorBase()
{

}

void ActorBase::Init()
{
	CreateComponents();
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
	/*DrawRotaGraph(
		actorParameterPtr_->drawPos.x,
		actorParameterPtr_->drawPos.y,
		actorParameterPtr_->scale,
		actorParameterPtr_->angle,
		actorParameterPtr_->texuresHandle[parameterAnimation_.animationIndex],
		actorParameterPtr_->transparent,
		actorParameterPtr_->direction
	);*/
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

void ActorBase::CreateComponents()
{
	// 必要なコンポーネントの生成
	std::unique_ptr<FactoryComponent> factoryComponent = std::make_unique<FactoryComponent>();
	for (const std::string& name : DEFAULT_COMPONENT_CREATE_LIST)
	{
		AddComponent(name, std::move(factoryComponent->CreateComponent(name, *this)));
	}
}
