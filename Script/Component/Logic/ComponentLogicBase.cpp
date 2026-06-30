#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "ComponentLogicBase.h"

ComponentLogicBase::ComponentLogicBase(EnemyBase& owner) :
	ComponentBase(owner),
	sceneManager_(SceneManager::GetInstance()),
	collisionManager_(CollisionManager::GetInstance()),
	gimmickManager_(GimmickManager::GetInstance()),
	spriteEffectManager_(SpriteEffectManager::GetInstance()),
	playerManager_(PlayerManager::GetInstance())
{
	// コンストラクタは変数の初期化のみ
	isEnd_ = false;
	probability_ = 0.0f;
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

void ComponentLogicBase::AttackReset()
{
	// 攻撃のコライダーとかがある場合ここで判定リセット
}