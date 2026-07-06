#include "ParameterActor.h"

ParameterActor::ParameterActor() :
	scale_(1.0f),
	angle_(0.0f),
	alpha_(1.0f),
    drawIndex_(0.0f),
	direction_(false), 
	transparent_(true), 
	localPos_({ 0, 0 }), 
	drawPos_({ 0, 0 }), 
    drawSize_({ 0, 0 }),
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
	hitSize_({ 0, 0 }), 
	hitRadius_(0.0f),
    texture_(-1),
    spriteTexture_(nullptr),    
    hp_(-1),
    hpMax_(-1),
    attackPower_(-1),
    attackBoostRate_(0.0f),
    knockBackPower_({ 0.0f, 0.0f }),
    color_(VECTOR{ 1.0f,1.0f,1.0f })
{
}

ParameterActor::~ParameterActor()
{
}

void ParameterActor::LoadParameter(const Json& parameter)
{
    // JSONから値を抽出してメンバ変数へ代入
    hpMax_ = parameter.value("hp", -1);
    attackPower_ = parameter.value("attackPower", -1);
    scale_ = parameter.value("scale", 1.0f);
    angle_ = parameter.value("angle", 0.0f);
    direction_ = parameter.value("direction", false);
    transparent_ = parameter.value("transparent", false);
    moveSpeed_ = parameter.value("moveSpeed", 0.0f);
    gravityPower_ = parameter.value("gravityPower", 0.0f);
    weight_ = parameter.value("weight", 0.0f);
    hitRadius_ = parameter.value("hitRadius", 0.0f);
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

    // 色の設定
    if (parameter.contains("color"))
    {
        color_.x = parameter["color"].value("r", 1.0f);
        color_.y = parameter["color"].value("g", 1.0f);
        color_.z = parameter["color"].value("b", 1.0f);
    }

    // 体力の反映
    hp_ = hpMax_;
}

Vector2 ParameterActor::GetScaleToHitSize()
{
    return Vector2F::MulVector2FFloat(hitSize_.ToVector2F(), scale_).ToVector2();
}

Vector2F ParameterActor::GetGravityDirectionVector() 
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

Vector2F ParameterActor::GetFront()
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
        vec = Vector2F::MulVector2FFloat(vec, -1.0f);
    }

    return vec;
}

Vector2F ParameterActor::GetBack()
{
    // 後ろ方向は前方向を完全に反転させたもの
    Vector2F vec = GetFront();
    vec = Vector2F::MulVector2FFloat(vec, -1.0f);
    return vec;
}

Vector2F ParameterActor::GetUp()
{
    // 上方向は重力ベクトルを完全に反転させたもの
    Vector2F vec = GetGravityDirectionVector();
    vec = Vector2F::MulVector2FFloat(vec, -1.0f);
    return vec;
}

Vector2F ParameterActor::GetDown() 
{
    // 下方向は重力ベクトルそのもの
    return GetGravityDirectionVector();
}

void ParameterActor::LoadParameterAnimation(const Json& jsonParameter)
{
    for (auto it = jsonParameter["animation"].begin(); it != jsonParameter["animation"].end(); ++it)
    {
        std::string animationName = it.key();
        Animation::Data animationData = {};
        auto& data = it.value();
        animationData.startIndex = data["no"].get<int>() * divisionNum_.x;
        animationData.endIndex = data["num"].get<int>() + animationData.startIndex - 1;
        animationData.animationSpeed = data["speed"].get<float>();

        // アニメーション情報を格納
        animationDataMap_.emplace(animationName, animationData);
    }
}