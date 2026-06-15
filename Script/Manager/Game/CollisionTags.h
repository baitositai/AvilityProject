#pragma once
#include <string>
#include <map>

class CollisionTags
{
public:

	// 衝突物の種類
	enum class TAG
	{
		NONE,
		PLAYER,						// プレイヤー
		PLAYER_ATTACK_NORMAL,		// プレイヤーの通常攻撃	
		PLAYER_AVILITY_STAMP,		// プレイヤーのアビリティ
		PLAYER_AVILITY_SHOT,		// プレイヤーのアビリティ
		STAGE,						// ステージ
		ENEMY_CLONE,				// 敵:クローン
		ENEMY_VIEW,					// 敵の視界
		ENEMY_ATTACK_NORMAL,		// 敵の攻撃
		//AVILITY_BOX,				// アビリティ設置のボックス
		BLAST,						// 爆風
		AIRSLASH,					// エアースラッシュ
		ITEM_AVILITY,				// アイテム:アビリティ
		TELEPORT_EXIT,				// テレポート
		DOOR,						// ドア
		CHANGE_NEXT_AREA,			// 次へ遷移するエリア
		TARGET,						// ターゲット
		TREASURE_CHEST,				// 宝箱
		MAX
	};

	// タグの数
	static constexpr int TAG_COUNT = static_cast<int>(TAG::MAX);

	// 各種タグの名前を管理するマップ
	static const std::map<TAG, std::string> TAG_NAME_MAP;
};

