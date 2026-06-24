#pragma once
#include "UiPlayerBase.h"

class UiPlayerSelectAvility : public UiPlayerBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiPlayerSelectAvility(const Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiPlayerSelectAvility() override;

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

	// バー用ハンドル
	int barHandle_;

	// バーの長さ
	float barLength_;

	// バーのサイズ
	Vector2 barSize_;

	// バー位置
	Vector2 barPos_;

};

