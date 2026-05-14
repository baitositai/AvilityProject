#pragma once
#include <unordered_map>
#include <string>

class AvilityTypes
{
public:

	enum class TYPE
	{
		SHOT,			// ショット
		BOX,			// ボックス
		STAMP,			// スタンプ
		GRAVITY,		// 重力変化
		TELEPORT,		// テレポート
		GIANT,			// 巨大化
		METAL,			// メタル
		AIRWALK,		// 空中歩行
		AIRSLASH,		// 空中斬り
		SUPERMAN,		// スーパーマン
		MAX
	};

	// アビリティの名前を管理
	static const std::unordered_map<TYPE, std::string> AVILITY_NAME_MAP;
};

