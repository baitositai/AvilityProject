#include "../../Manager/Common/SceneManager.h"
#include "EffectAirslash.h"

EffectAirslash::EffectAirslash(std::unique_ptr<ParameterEffect> parameter, const Vector2F& direction) :
	direction_(direction),
	EffectBase(std::move(parameter))
{
	time_ = 0.0f;
	parameterEffect_ = GetParameterEffectPtr();
}

EffectAirslash::~EffectAirslash()
{
}

void EffectAirslash::Init()
{
}

void EffectAirslash::Update()
{
	// 時間経過で消滅
	time_ += SceneManager::GetInstance().GetDeltaTime();
	if (time_ >= ALIVE_TIME) 
	{
		isDelete_ = true;
	}

	// 指定した方向に座標を更新
	
}