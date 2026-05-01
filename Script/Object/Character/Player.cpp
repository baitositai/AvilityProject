#include <DxLib.h>
#include "../../Component/Avility/ComponentAvilityShot.h"
#include "../../Component/Avility/ComponentAvilityChargeShot.h"
#include "../../OnHit/OnHitPlayer.h"
#include "../../Collider/ColliderBox.h"
#include ".././Utility/UtilityCommon.h"
#include "../Common/Animation.h"
#include "Player.h"

Player::Player(const Parameter& parameter, const std::unordered_map<std::string, std::string> stateComponentNameList, const std::vector<std::string> defaultComponentNameList, std::unique_ptr<Animation> animation) :
	parameter_(parameter),
	CharacterBase(&parameter_, stateComponentNameList, defaultComponentNameList, std::move(animation))
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
}

void Player::Update()
{
	CharacterBase::Update();
}

void Player::DebugDraw()
{
	CharacterBase::DebugDraw();
	DrawFormatString(0, 20, UtilityCommon::LIME, L"ジャンプ力    :%2f", parameter_.jumpPow);
	DrawFormatString(0, 40, UtilityCommon::LIME, L"プレイヤー位置:%2f,%2f", parameter_.pos.x, parameter_.pos.y);
}

void Player::AttackReset()
{
	// 初期化
	componentStateMap_.at(STATE::ATTACK)->Init();
}
