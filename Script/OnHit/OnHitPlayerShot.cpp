#include "../Object/Character/Player.h"
#include "../Collider/ColliderBase.h"
#include "OnHitPlayerShot.h"

OnHitPlayerShot::OnHitPlayerShot(Player& owner) :
	OnHitBase(owner),
	owner_(owner)
{
}

OnHitPlayerShot::~OnHitPlayerShot()
{
}

void OnHitPlayerShot::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// パラメータ取得
	auto& parameter = owner_.GetParameter();

	// インターバル時間がない場合
	if (parameter.shotDamageInterval_ < 0.0f)
	{
		// ダメージインターバル設定
		parameter.shotDamageInterval_ = 0.2f;

		// ショット時間を減少
		parameter.shotTime_ -= 0.5f;

		// 敵のダメージ処理
		auto opponent = opponentCollider.lock();
		opponent->GetOwner().Damage(owner_.GiveDamage(), opponent->GetHitPos());
	}
}
