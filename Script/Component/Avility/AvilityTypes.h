#pragma once
#include <unordered_map>
#include <string>

class AvilityTypes
{
public:

	enum class TYPE
	{
		SUPERMAN,		// スーパーマン
		AIRWALK,		// 空中歩行
		GRAVITYCONTROLL,		// 重力変化
		SHOT,			// ショット
		AIRSLASH,		// 空中斬り
		METAL,			// メタル
		STAMP,			// スタンプ
		TELEPORT,		// テレポート
		GIANT,			// 巨大化
		//BOX,			// ボックス
		MAX
	};

	// 最大数
	static constexpr int AVILITY_TYPE_MAX = static_cast<int>(TYPE::MAX);

	// アビリティの名前を管理
	static const std::unordered_map<TYPE, std::string> AVILITY_NAME_MAP;
};

