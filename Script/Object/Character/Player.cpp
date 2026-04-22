#include <DxLib.h>
#include "../../OnHit/OnHitPlayer.h"
#include "../Collider/ColliderBox.h"
#include "Player.h"

#include "../../Component/Avility/ComponentAvilityShot.h"

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
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::PLAYER, parameter_.hitBoxSize);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitPlayer>(*this);
	
	// 基底クラスの初期化
	CharacterBase::Init();

	// デバッグ用
	componentMap_.try_emplace(std::string("AvilityShot"), std::make_unique<ComponentAvilityShot>(*this));
}

void Player::Update()
{
	CharacterBase::Update();
}

void Player::DebugDraw()
{
	CharacterBase::DebugDraw();
	DrawFormatString(0, 20, 0x00ff00, L"プレイヤー位置:%2f,%2f", parameter_.pos.x, parameter_.pos.y);
}
