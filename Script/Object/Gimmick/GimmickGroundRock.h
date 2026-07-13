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

	//ジャンプ力
	static constexpr float JUMP_POW_MAX = -5.0f;

	//速度横移動速度最大
	static constexpr float JUMP_SPD_MIN = 3.0f;
	static constexpr float JUMP_SPD_MAX = 10.0f;

	//角度最大
	static constexpr float ANGLE_MAX = 360.0f;

	//回転速度(デグリー)
	static constexpr float ANGLE_SPD = 10.0f;

	// パラメータ情報
	ParameterGimmick* parameterGroundRock_;

	//更新処理
	std::function<void(void)> update_;

	//ヒット用半径の大きさ
	float hitRadius_;

	//ジャンプ力
	float jumpPow_;

	float velocity_;

	//横移動速度
	float horizonSpd_;
	// 接地判定の共通ロジック
	void CheckGroundStatus(float moveVal, bool isXAxis);
};

