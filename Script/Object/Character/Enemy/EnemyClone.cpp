#include "../../../Collider/ColliderBox.h"
#include "../../../OnHit/OnHitEnemyClone.h"
#include "EnemyClone.h"

EnemyClone::EnemyClone(const Parameter& parameter, const std::unordered_map<std::string, std::string> stateComponentNameList, const std::vector<std::string> defaultComponentNameList) :
	parameter_(parameter),
	CharacterBase(&parameter_, stateComponentNameList, defaultComponentNameList)
{
}

EnemyClone::~EnemyClone()
{
}

void EnemyClone::Init()
{
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_CLONE, parameter_.pos, parameter_.hitBoxSize, parameter_.angle);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEnemyClone>(*this);

	// 基底クラスの初期化
	CharacterBase::Init();
}

void EnemyClone::InitAnimation()
{
	// アニメーションの登録
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::IDLE), parameter_.animationsIdle);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::WALK), parameter_.animationsWalk);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::BRAKE), parameter_.animationsBrake);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::ATTACK), parameter_.animationsAttack);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::JUMP), parameter_.animationsJump);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::FALL), parameter_.animationsFall);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::DIE), parameter_.animationsDie);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::DAMAGE), parameter_.animationsDamage);
	parameterAnimation_.animationsMap.emplace(static_cast<int>(ANIMATION::PAUSE), parameter_.animationsPause);

	// 初期アニメーション速度の登録
	parameterAnimation_.animationSpeed = parameter_.animationSpeed;

	// 初期アニメーション
	ChangeAnimation(ANIMATION::IDLE);
}

void EnemyClone::ChangeAnimation(const ANIMATION type, const bool isLoop)
{
	// 型変換
	int intType = static_cast<int>(type);

	// 同じアニメーション種類の場合無視
	if (intType == parameterAnimation_.animationType) return;

	// 種類格納
	parameterAnimation_.animationType = intType;

	// 開始インデックス格納
	parameterAnimation_.animationStartIndex = parameterAnimation_.animationType * parameter_.divisionNum.x;

	// 終了インデックス格納
	parameterAnimation_.animationFinishIndex = parameterAnimation_.animationStartIndex + parameterAnimation_.animationsMap.at(parameterAnimation_.animationType) - 1;

	// ループ判定
	parameterAnimation_.isLoop = isLoop;

	// 再生判定
	parameterAnimation_.isPlay = true;
}