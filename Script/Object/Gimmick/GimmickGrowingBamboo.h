#pragma once
#include "GimmickBase.h"
#include "../../Parameter/Gimmick/ParameterGimmickGrowingBamboo.h"

class GimmickGrowingBamboo : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickGrowingBamboo(std::unique_ptr<ParameterGimmickGrowingBamboo> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickGrowingBamboo() override;

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

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterGimmickGrowingBamboo& GetParameter() { return *parameterBamboo_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterGimmickGrowingBamboo& GetParameter() const { return *parameterBamboo_; }

private:

	// 成長インターバル
	static constexpr float GROWING_INTERVAL = 0.05;

	// 成長回数カウント
	int growingCount_;

	// タイマー
	float timer_;

	// 成長長さ
	float growLength_;

	// 更新処理
	std::function<void()> update_;

	// パラメータ情報
	ParameterGimmickGrowingBamboo* parameterBamboo_;

	// 描画の初期化
	void InitDraw() override {};

	// 成長処理
	void UpdateGrow();

	// 待機処理
	void UpdateWait();
};