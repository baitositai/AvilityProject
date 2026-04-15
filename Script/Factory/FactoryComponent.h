#pragma once
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include "../Component/ComponentBase.h"

class ComponentBase;
class ComponentSpriteAnimation;
class ComponentActionPlayer;

class FactoryComponent
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	FactoryComponent();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FactoryComponent();

	/// <summary>
	/// コンポーネントの生成
	/// </summary>
	/// <param name="name">名前</param>
	std::unique_ptr<ComponentBase> CreateComponent(const std::string& name);

private:

	// コンポーネント生成マップ
	std::unordered_map<std::string, std::function<std::unique_ptr<ComponentBase>()>> componentCreateMap_;

	// 各種コンポーネント生成処理
	std::unique_ptr<ComponentSpriteAnimation> CreateComponentSpriteAnimation();
	std::unique_ptr<ComponentActionPlayer> CreateComponentActionPlayer();
};

