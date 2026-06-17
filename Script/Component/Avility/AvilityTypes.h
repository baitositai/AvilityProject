#pragma once
#include <unordered_map>
#include <string>

class AvilityTypes
{
public:

	enum class TYPE
	{
		SHOT,			// ショット
		//BOX,			// ボックス
		STAMP,			// スタンプ
		GRAVITYCONTROLL,		// 重力変化
		TELEPORT,		// テレポート
		GIANT,			// 巨大化
		METAL,			// メタル
		AIRWALK,		// 空中歩行
		AIRSLASH,		// 空中斬り
		SUPERMAN,		// スーパーマン
		MAX
	};

	// 最大数
	static constexpr int AVILITY_TYPE_MAX = static_cast<int>(TYPE::MAX);

	// アビリティの名前を管理
	static const std::unordered_map<TYPE, std::string> AVILITY_NAME_MAP;
};

