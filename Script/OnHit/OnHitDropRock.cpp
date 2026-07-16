#include "../../Manager/Common/SpriteEffectManager.h"
#include "../Object/Gimmick/GimmickDropRock.h"
#include "OnHitDropRock.h"

OnHitDropRock::OnHitDropRock(GimmickDropRock& owner):
	OnHitBase(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::STAGE,[this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
}

OnHitDropRock::~OnHitDropRock()
{
}

void OnHitDropRock::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	//削除処理
	owner_.Delete();

	//エフェクト再生
	ParameterGimmick param = owner_.GetParameter();
	SpriteEffectManager::CreateParameter parameter = {};
	parameter.pos = param.pos_;
	parameter.scale = param.scale_;
	parameter.resourceKey = "rockBreak";
	parameter.animationSpeed = 0.2f;
	SpriteEffectManager::GetInstance().Create(parameter);
}