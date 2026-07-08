#pragma once
#include "ParameterItem.h"
#include "../../Manager/Game/CollisionTags.h"

class ParameterItemPotion : public ParameterItem
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItemPotion();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterItemPotion() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <param name="name">名前</param>
	void LoadParameter(const Json& parameter, std::string& name);

	// 最大体力上昇
	int hpMaxUp_;

	// 攻撃力上昇
	int attackUp_;

	// 速度上昇
	float speedUp_;

	// 衝突判定タグ
	CollisionTags::TAG tag_;

private:

	// 衝突判定タグの取得用map
	const std::unordered_map<std::string, CollisionTags::TAG> NAME_TAG_MAP = {
		{"potionAttackUp", CollisionTags::TAG::ITEM_ATTACK_UP},
		{"potionSpeedUp", CollisionTags::TAG::ITEM_SPEED_UP },
		{"potionHpMaxUp", CollisionTags::TAG::ITEM_HPMAX_UP}
	};
};