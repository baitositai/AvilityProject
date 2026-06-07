#include "../../Utility/UtilityCommon.h"
#include "ParameterEnemy.h"

ParameterEnemy::ParameterEnemy() : 
	isDiscover_(false),
	goalPos_({}),
	eyeAngle_(0.0f),
	eyeAngleRad_(0.0f),
	eyeDistance_(0.0f),
	attackStartDistance_(0.0f),
	permissibleDistance_(0.0f),
	habitatType_(HABITAT_TYPE::MAX)
{
	targetPos_ = nullptr;
}

ParameterEnemy::~ParameterEnemy()
{
}

void ParameterEnemy::LoadParameter(const Json& parameter)
{
	// 基底クラスの読み込み処理
	ParameterCharacter::LoadParameter(parameter);

	// 敵固有のパラメータの読み込み
	eyeAngle_ = parameter.value("eyeAngle", 0.0f);
	eyeDistance_ = parameter.value("eyeDistance", 0.0f);
    attackStartDistance_ = parameter.value("attackStartDistance", 0.0f);
	permissibleDistance_ = parameter.value("permissibleDistance", 0.0f);
	spawnRate_ = parameter.value("spawnRate", 0.0f);
	std::string habitatTypeString = parameter.value("habitatType", "land");

	// 視野角度をラジアンに変換
	eyeAngleRad_ = UtilityCommon::Deg2RadF(eyeAngle_);

	// 移動種類を列挙型へ変換
	habitatType_ = HABITAT_TYPE_STRING_TO_ENUM.at(habitatTypeString);
}