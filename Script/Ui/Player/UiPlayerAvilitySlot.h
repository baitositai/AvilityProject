#pragma once
#include <vector>
#include "UiPlayerBase.h"

class UiPlayerAvilitySlot : public UiPlayerBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiPlayerAvilitySlot(const Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiPlayerAvilitySlot() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	// アビリティスロット番号
	std::vector<int> avilitySlotIndexs_;

	// リソースハンドル
	int* avilitySlotHandle_;
};

