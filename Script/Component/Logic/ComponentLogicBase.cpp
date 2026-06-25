#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "ComponentLogicBase.h"

ComponentLogicBase::ComponentLogicBase(EnemyBase& owner) :
	ComponentBase(owner),
	sceneManager_(SceneManager::GetInstance()),
	collisionManager_(CollisionManager::GetInstance())
{
	// コンストラクタは変数の初期化のみ
	isEnd_ = false;
}

ComponentLogicBase::~ComponentLogicBase()
{
	// 削除処理はRemoveで行う
}

void ComponentLogicBase::Create()
{
	// コライダーの登録などの生成時にのみ行う処理など(ついでに初期化も行う)
}

void ComponentLogicBase::Init()
{
	// 定期的に親コンポーネントが初期化されるためその際の処理
	isEnd_ = false;
}

void ComponentLogicBase::Update()
{
}

void ComponentLogicBase::Remove()
{
}

const float ComponentLogicBase::GetProbability() const
{
	return 0.0f;
}
