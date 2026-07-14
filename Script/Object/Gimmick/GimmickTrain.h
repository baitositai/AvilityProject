#include "GimmickBase.h"
#include "../../Parameter/Gimmick/ParameterGimmickTrain.h"

class GimmickTrain : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickTrain(std::unique_ptr<ParameterGimmickTrain> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickTrain() override;

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

	// 状態
	enum class STATE
	{
		WAIT,
		PASSING,
		MAX
	};

	// 待機時間
	static constexpr int WAIT_TIME_MAX = 50;
	static constexpr int WAIT_TIME_MIN = 40;

	// パラメータ情報
	ParameterGimmickTrain* parameterTrain_;

	// 状態
	STATE state_;

	// タイマー
	float timer_;

	// 更新処理
	std::function<void()> update_;

	// 状態遷移管理
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// 状態別処理
	void UpdateWait();
	void UpdatePassing();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateWait();
	void ChangeStatePassing();

	// 描画初期化
	void InitDraw() override;
};