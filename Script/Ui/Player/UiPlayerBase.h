#pragma once
#include "../UiBase.h"

class Player;
class ResourceManager;

class UiPlayerBase : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiPlayerBase(const Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UiPlayerBase() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() override;

protected:

	// 所有者
	const Player& owner_;

	// ベースとなる位置
	Vector2 basePos_;

	// プレイヤー番号
	int playerNum_;
};

