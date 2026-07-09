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
		ENEMY_BASE,					// 敵:基本
		ENEMY_MAID,					// 敵:メイド
		ENEMY_VIEW,					// 敵の視界
		ENEMY_ATTACK_NORMAL,		// 敵の攻撃
		//AVILITY_BOX,				// アビリティ設置のボックス
		BLAST,						// 爆風
		AIRSLASH,					// エアースラッシュ
		ITEM_AVILITY,				// アイテム:アビリティ
		ITEM_TREASURE,				// アイテム:宝
		ITEM_FOOD,					// アイテム:食べ物
		ITEM_MONEY,					// アイテム:お金
		ITEM_ATTACK_UP,				// アイテム:攻撃力上昇ポーション
		ITEM_HPMAX_UP,				// アイテム:最大体力上昇ポーション
		ITEM_SPEED_UP,				// アイテム:スピード上昇ポーション
		TELEPORT_EXIT,				// テレポート
		DOOR,						// ドア
		CHANGE_NEXT_AREA,			// 次へ遷移するエリア
		TARGET,						// ターゲット
		TREASURE_CHEST,				// 宝箱
		BAMBOO,						// 竹
		SHOP,						// 店
		DROP_ROCK,					// 岩落とし
		MAX
	};

	// タグの数
	static constexpr int TAG_COUNT = static_cast<int>(TAG::MAX);

	// 各種タグの名前を管理するマップ
	static const std::map<TAG, std::string> TAG_NAME_MAP;
};

