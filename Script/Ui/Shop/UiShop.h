#pragma once
#include "../UiBase.h"

class GimmickShop;

class UiShop : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiShop(const GimmickShop& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiShop() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	const GimmickShop& owner_;
	Vector2 basePos_;
	float timer_;
};