#include <DxLib.h>
#include "../../Component/Avility/ComponentAvilityShot.h"
#include "../../OnHit/OnHitPlayer.h"
#include "../Collider/ColliderBox.h"
#include "Player.h"

<<<<<<< HEAD
#include "../../Component/Avility/ComponentAvilityShot.h"
#include "../../Component/Avility/ComponentAvilityChargeShot.h"

Player::Player(const Parameter& parameter, const std::vector<std::string> componentNameList):
=======
Player::Player(const Parameter& parameter, const std::unordered_map<std::string, std::string> stateComponentNameList, const std::vector<std::string> defaultComponentNameList) :
>>>>>>> origin/AvilityBox
	parameter_(parameter),
	CharacterBase(&parameter_, stateComponentNameList, defaultComponentNameList)
{
}

Player::~Player()
{
}

void Player::Init()
{	
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::PLAYER, parameter_.pos, parameter_.hitBoxSize,parameter_.angle);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitPlayer>(*this);
	
	// 基底クラスの初期化
	CharacterBase::Init();

	// デバッグ用
	componentMap_.try_emplace(std::string("AvilityShot"), std::make_unique<ComponentAvilityShot>(*this));
	componentMap_.try_emplace(std::string("AvilityChargeShot"), std::make_unique<ComponentAvilityChargeShot>(*this));
}

void Player::Update()
{
	CharacterBase::Update();
}

void Player::DebugDraw()
{
	CharacterBase::DebugDraw();
	DrawFormatString(0, 20, 0x000000, L"プレイヤー位置:%2f,%2f", parameter_.pos.x, parameter_.pos.y);
	DrawFormatString(0, 40, 0x000000, L"アニメーション種類:%d", parameterAnimation_.animationType);
}

void Player::InitAnimation()
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

void Player::ChangeAnimation(const ANIMATION type, const bool isLoop)
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