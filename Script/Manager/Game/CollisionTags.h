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
		PLAYER,					// プレイヤー
		PLAYER_ATTACK_NORMAL,	// プレイヤーの通常攻撃			
		STAGE,					// ステージ
		ENEMY_CLONE,			// 敵:クローン
		AVILITY_BOX,			// アビリティ設置のボックス
		BLAST,
		MAX
	};

	// タグの数
	static constexpr int TAG_COUNT = static_cast<int>(TAG::MAX);

	// 各種タグの名前を管理するマップ
	static const std::map<TAG, std::string> TAG_NAME_MAP;
};

