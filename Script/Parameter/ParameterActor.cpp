#include "ParameterActor.h"

ParameterActor::ParameterActor() :
	scale_(1.0f),
	angle_(0.0f),
	direction_(false), 
	transparent_(true), 
	localPos_({ 0, 0 }), 
	drawPos_({ 0, 0 }), 
	divisionNum_({ 0, 0 }), 
	moveSpeed_(0.0f), 
	moveSpeedBoostRate_(0.0f), 
	pos_({ 0.0f, 0.0f }), 
	moveAmount_({ 0.0f, 0.0f }), 
	gravityPower_(0.0f), 
	gravityBoostRate_(0.0f), 
	gravityDir_(DIR::DOWN), 
	weight_(0.0f),
	isGround_(false), 
	isFall_(false), 
	hitSize_({ 0, 0 }), 
	hitRadius_(0.0f)
{
}

ParameterActor::~ParameterActor()
{
}

void ParameterActor::LoadParameter(const Json& parameter)
{
    // JSONから値を抽出してメンバ変数へ代入
    scale_ = parameter.value("scale", 1.0f);
    angle_ = parameter.value("angle", 0.0f);
    direction_ = parameter.value("direction", false);
    transparent_ = parameter.value("transparent", false);
    moveSpeed_ = parameter.value("moveSpeed", 0.0f);
    gravityPower_ = parameter.value("gravityPower", 0.0f);
    weight_ = parameter.value("weight", 0.0f);
    resourceKey_ = parameter.value("resourceKey", "");
    componentkeys_ = parameter.value("componentKeys", std::vector<std::string>());

    // 分割数の読み込み
    if (parameter.contains("divisionNum"))
    {
        divisionNum_.x = parameter["divisionNum"].value("x", 1);
        divisionNum_.y = parameter["divisionNum"].value("y", 1);
    }

    // ヒットボックスサイズの読み込み
    if (parameter.contains("hitBoxSize"))
    {
        hitSize_.x = parameter["hitBoxSize"].value("x", 0);
        hitSize_.y = parameter["hitBoxSize"].value("y", 0);
    }

    // 相対位置の読み込み
    if (parameter.contains("localPos"))
    {
        localPos_.x = parameter["localPos"].value("x", 0);
        localPos_.y = parameter["localPos"].value("y", 0);
    }

    // 初期位置の設定
    if (parameter.contains("pos"))
    {
        pos_.x = parameter["pos"].value("x", 0);
        pos_.y = parameter["pos"].value("y", 0);
    }
}

const Vector2F ParameterActor::GetGravityDirectionVector() const
{
    Vector2F dir = {};

    switch (gravityDir_)
    {
    case DIR::RIGHT:  dir = Vector2F(1.0f, 0.0f);  break;
    case DIR::LEFT:   dir = Vector2F(-1.0f, 0.0f); break;
    case DIR::UP:     dir = Vector2F(0.0f, -1.0f); break;
    case DIR::DOWN:   dir = Vector2F(0.0f, 1.0f);  break;
    }

    return dir;
}

const Vector2F ParameterActor::GetFront() const
{
    Vector2F vec = {};

    // 重力方向に応じた基準の右方向（前方向）を計算
    switch (gravityDir_)
    {
    case DIR::RIGHT: vec = Vector2F(0.0f, -1.0f); break; // 重力が右なら前は上
    case DIR::LEFT:  vec = Vector2F(0.0f, 1.0f);  break; // 重力が左なら前は下
    case DIR::UP:    vec = Vector2F(-1.0f, 0.0f); break; // 重力が上なら前は左
    case DIR::DOWN:  vec = Vector2F(1.0f, 0.0f);  break; // 重力が下なら前は右
    }

    // キャラクターの向きが左（true）なら前方向を反転させる
    if (direction_)
    {
        Vector2F::MulVector2FFloat(vec, -1.0f);
    }

    return vec;
}

const Vector2F ParameterActor::GetBack() const
{
    // 後ろ方向は前方向を完全に反転させたもの
    Vector2F vec = GetFront();
    Vector2F::MulVector2FFloat(vec, -1.0f);
    return vec;
}

const Vector2F ParameterActor::GetUp() const
{
    // 上方向は重力ベクトルを完全に反転させたもの
    Vector2F vec = GetGravityDirectionVector();
    Vector2F::MulVector2FFloat(vec, -1.0f);
    return vec;
}

const Vector2F ParameterActor::GetDown() const
{
    // 下方向は重力ベクトルそのもの
    return GetGravityDirectionVector();
}