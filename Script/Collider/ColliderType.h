#pragma once
#include <map>
#include <string>

class ColliderType
{
public:

	// コライダーの種類
	enum class TYPE
	{
		NONE,		// なし
		BOX,		// ボックス
		CIRCLE,		// サークル
		LINE,		// ライン
		ARRAY,		// 配列
		MAX,		// 最大値
	};

	// コライダー種別名前管理マップ
	static const std::map<TYPE, std::string> TYPE_NAME_MAP;

	// コライダー種類数
	static constexpr int COLLIDER_TYPES = static_cast<int>(TYPE::MAX);
};

