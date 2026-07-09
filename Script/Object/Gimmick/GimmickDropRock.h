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
	/// 岩生成
	/// </summary>
	/// <param name="_createPos"></param>
	void CreateRock(const Vector2F _createPos);

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

	// パラメータ情報
	ParameterGimmick* parameterDropRock_;

	//状態
	STATE state_;
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
	void ChangeCreate(void);
	void UpdateWait(void);
	void UpdateDrop(void);
};

