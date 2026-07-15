#pragma once
#include "GimmickBase.h"

class ParameterGimmick;

class GimmickDropRock :
    public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickDropRock(std::unique_ptr<ParameterGimmick> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickDropRock() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterGimmick& GetParameter() { return *parameterDropRock_; }

private:

	enum class STATE
	{
		NONE,
		WAIT,
		DROP
	};

	//岩サイズ
	static constexpr float ROCK_SIZE = 50.0f;

	//待機時間
	static constexpr float WAIT_TIME = 3.0f;

	//カメラシェイク関連
	static constexpr float CAMERA_SHAKE_TIME = 0.2f;
	static constexpr float CAMERA_SHAKE_POWER = 2.0f;

	// パラメータ情報
	ParameterGimmick* parameterDropRock_;

	//状態
	STATE state_;

	//更新処理
	std::function<void(void)> update_;

	//待機時間
	float waitCnt_;

	//ヒット用半径の大きさ
	float hitRadius_;

	//生存状態
	bool isDead_;

	// 接地判定の共通ロジック
	void CheckGroundStatus(float moveVal, bool isXAxis);

	//Drop待機状態
	void UpdateWait();
	void UpdateDrop();

	//地面から岩が出てくる攻撃
	void UpdateGroundRock();


};

