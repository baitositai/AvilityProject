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
class ComponentKnockBack;
class ComponentInvincible;
class ComponentJump;

class ComponentStatePlayerProcess;
class ComponentStateAttackDefault;
class ComponentStateIdle;
class ComponentStateDead;
class ComponentStateDummy;

class ComponentAvilityBase;
class ComponentAvilityBox;
class ComponentAvilityShot;
class ComponentAvilityGravity;
class ComponentAvilityStamp;
class ComponentAvilityAirwalk;
class ComponentAvilitySuperman;
class ComponentAvilityMetal;
class ComponentAvilityAirslash;

class ComponentDebugCreateItemAvility;

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

	/// <summary>
	/// アビリティコンポーネントの生成
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="owner">所有者</param>
	/// <returns>生成されたアビリティコンポーネント</returns>
	std::unique_ptr<ComponentAvilityBase> CreateComponentAvility(const std::string& name, ActorBase& owner);

private:

	// コンポーネント生成マップ
	std::unordered_map<std::string, std::function<std::unique_ptr<ComponentBase>(ActorBase& owner)>> componentCreateMap_;

	// 各種コンポーネント生成処理
	std::unique_ptr<ComponentMove> CreateComponentMove(ActorBase& owner);
	std::unique_ptr<ComponentSpriteAnimation> CreateComponentSpriteAnimation(ActorBase& owner);
	std::unique_ptr<ComponentGravity> CreateComponentGravity(ActorBase& owner);
	std::unique_ptr<ComponentStatePlayerProcess> CreateComponentStatePlayerProcess(ActorBase& owner);
	std::unique_ptr<ComponentStateAttackDefault> CreateComponentStateAttackDefault(ActorBase& owner);
	std::unique_ptr<ComponentAvilityBox> CreateComponentAvilityBox(ActorBase& owner);
	std::unique_ptr<ComponentAvilityStamp> CreateComponentAvilityStamp(ActorBase& owner);
	std::unique_ptr<ComponentAvilityAirwalk> CreateComponentAvilityAirwalk(ActorBase& owner);
	std::unique_ptr<ComponentAvilityShot> CreateComponentAvilityShot(ActorBase& owner);
	std::unique_ptr<ComponentAvilityGravity> CreateComponentAvilityGravity(ActorBase& owner);
	std::unique_ptr<ComponentAvilityMetal> CreateComponentAvilityMetal(ActorBase& owner);
	std::unique_ptr<ComponentAvilitySuperman> CreateComponentAvilitySuperman(ActorBase& owner);
	std::unique_ptr<ComponentAvilityAirslash> CreateComponentAvilityAirslash(ActorBase& owner);
	std::unique_ptr<ComponentKnockBack> CreateComponentKnockBack(ActorBase& owner);
	std::unique_ptr<ComponentStateIdle> CreateComponentStateIdle(ActorBase& owner);
	std::unique_ptr<ComponentStateDead> CreateComponentStateDead(ActorBase& owner);
	std::unique_ptr<ComponentStateDummy> CreateComponentStateDummy(ActorBase& owner);
	std::unique_ptr<ComponentInvincible> CreateComponentInvincible(ActorBase& owner);
	std::unique_ptr<ComponentJump> CreateComponentJump(ActorBase& owner);
	std::unique_ptr<ComponentDebugCreateItemAvility> CreateComponentDebugCreateItemAvility(ActorBase& owner);
	
	// コンストラクタ
	FactoryComponent();

	// デストラクタ
	~FactoryComponent();
};