#pragma once
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include "../../Template/Singleton.h"
#include "../Component/ComponentBase.h"

class ComponentBase;
class ComponentMove;
class ComponentSpriteAnimation;
class ComponentGravity;
class ComponentStatePlayerAlive;
class ComponentStatePlayerAttack;
class ComponentStatePlayerDead;
class ComponentStatePlayerHit;
class ComponentStatePlayerRespawn;
class ComponentAvilityBox;
class ComponentAvilityShot;

class FactoryComponent : public Singleton<FactoryComponent>
{
	//シングルトンにだけ共有する
	friend class Singleton<FactoryComponent>;

public:

	/// <summary>
	/// コンポーネントの生成
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="owner">所有者</param>
	std::unique_ptr<ComponentBase> CreateComponent(const std::string& name, ActorBase& owner);

private:

	// コンポーネント生成マップ
	std::unordered_map<std::string, std::function<std::unique_ptr<ComponentBase>(ActorBase& owner)>> componentCreateMap_;

	// 各種コンポーネント生成処理
	std::unique_ptr<ComponentMove> CreateComponentMove(ActorBase& owner);
	std::unique_ptr<ComponentSpriteAnimation> CreateComponentSpriteAnimation(ActorBase& owner);
	std::unique_ptr<ComponentGravity> CreateComponentGravity(ActorBase& owner);
	std::unique_ptr<ComponentStatePlayerAlive> CreateComponentStatePlayerAlive(ActorBase& owner);
	std::unique_ptr<ComponentStatePlayerAttack> CreateComponentStatePlayerAttack(ActorBase& owner);
	std::unique_ptr<ComponentStatePlayerDead> CreateComponentStatePlayerDead(ActorBase& owner);
	std::unique_ptr<ComponentStatePlayerHit> CreateComponentStatePlayerHit(ActorBase& owner);
	std::unique_ptr<ComponentStatePlayerRespawn> CreateComponentStatePlayerRespawn(ActorBase& owner);	
	std::unique_ptr<ComponentAvilityBox> CreateComponentAvilityBox(ActorBase& owner);
	std::unique_ptr<ComponentAvilityShot> CreateComponentAvilityShot(ActorBase& owner);
	
	// コンストラクタ
	FactoryComponent();

	// デストラクタ
	~FactoryComponent();
};