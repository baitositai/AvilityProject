#include "../../Manager/Common/SceneManager.h"
#include "EffectAirslash.h"

EffectAirslash::EffectAirslash(const Vector2F& direction) :
	direction_(direction)
{
	time_ = 0.0f;
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
	if (time_ >= ALIVE_TIME) { isDelete_ = true; }

	// 指定した方向に座標を更新
	
}