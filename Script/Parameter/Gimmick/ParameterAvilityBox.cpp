#include "ParameterAvilityBox.h"

ParameterAvilityBox::ParameterAvilityBox()
{
}

ParameterAvilityBox::~ParameterAvilityBox()
{
}

void ParameterAvilityBox::LoadParameter(const Json& parameter)
{
}

void ParameterAvilityBox::Init()
{
		/*"moveSpeed" : 2.0,
		"dashSpeed" : 4.0,
		"hp" : 100,
		"attackPower" : 10,
		"jumpPowerMax" : 20.0,
		"gravityPower" : 9.8,
		"jumpCount" : 1,
		"jumpCountMax" : 1,
		"invincibleTimeMax" : 2.0,
		"defaultAttackRadius" : 20.0,
		"animationDefaultSpeed" : 0.1,
		"animationAttackSpeed" : 0.2,
		"animationsIdle" : 6,
		"animationsWalk" : 8,
		"animationsBrake" : 4,
		"animationsAttack" : 7,
		"animationsJump" : 6,
		"animationsFall" : 6,
		"animationsDie" : 10,
		"animationsDamage" : 4,
		"animationsPause" : 6,
		"weight" : 0.9,
		"divisionNum" : {
		"x": 10,
			"y" : 9
	},
		"hitBoxSize" : {
		"x": 48,
			"y" : 64
	},
		"localPos" : {
		"x": 0,
			"y" : 0
	},
		"defaultAttackLoaclPos" : {
		"x": 40,
			"y" : 8
	},*/
	// 拡大率
	scale_ = 1.0f;
	// 角度
	angle_ = 0.0f;
	// 向き false 右 true 左
	direction_ = false;
	// 透過判定
	transparent_ = true;
	// 相対位置
	localPos_ = Vector2(0, 0);
	// 描画位置
	drawPos_ = Vector2(0, 0);
	// 分割数
	divisionNum_ = Vector2(1, 1);
	// 移動速度
	moveSpeed_ = 0.0f;
	// 移動速度上昇率
	moveSpeedBoostRate_ = 0.0f;
	// 位置
	pos_ = Vector2F(0.0f, 0.0f);
	// 移動量
	moveAmount_ = Vector2F(0.0f, 0.0f);
	// 重力
	gravityPower_ = 5.0f;

	// 重力の上昇値
	float gravityBoostRate_;
	// 重力方向
	DIR gravityDir_;

	// 地面判定
	bool isGround_;

	// 落下判定
	bool isFall_;

	// ヒット半径
	float hitRadius_;

	hitSize_ = Vector2(48, 48);
	gravityPower_ = 0.5f;
	weight_ = 1.0f;
	blastTime_ = 3.0f;
}