#include "../../OnHit/OnHitPlayer.h"
#include "../Collider/ColliderBox.h"
#include "Player.h"

Player::Player(const Parameter& parameter, const std::vector<std::string> componentNameList):
	parameter_(parameter),
	CharacterBase(&parameter_, componentNameList)
{

}

Player::~Player()
{
}

void Player::Init()
{	
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::PLAYER, parameter_.hitBoxSize_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitPlayer>(*this);
	
	// 基底クラスの初期化
	CharacterBase::Init();
}

void Player::Update()
{
	CharacterBase::Update();
}
