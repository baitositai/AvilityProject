#pragma once
#include "GimmickBase.h"
class GimmickGroundRock :
    public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickGroundRock(std::unique_ptr<ParameterGimmick> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickGroundRock() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	//岩サイズ
	static constexpr float ROCK_SIZE = 50.0f;

	// パラメータ情報
	ParameterGimmick* parameterGroundRock_;

	//更新処理
	std::function<void(void)> update_;

	//ヒット用半径の大きさ
	float hitRadius_;

	// 接地判定の共通ロジック
	void CheckGroundStatus(float moveVal, bool isXAxis);
};

