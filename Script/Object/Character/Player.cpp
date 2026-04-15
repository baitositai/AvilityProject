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
}

void Player::Update()
{
}