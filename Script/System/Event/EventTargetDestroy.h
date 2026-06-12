#pragma once
#include "EventBase.h"
#include "../../Parameter/Event/ParameterEventTargetDestroy.h"

class EventTargetDestroy : public EventBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	EventTargetDestroy(std::unique_ptr<ParameterEventTargetDestroy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EventTargetDestroy() override;

private:

	// ターゲットの生成方法
	enum class TARGET_CREATE_PATTERN
	{
		FIX,		// 固定
		FIX_MOVE,	// 固定動き
		RANDOM,		// ランダム
		MAX			
	};

	// 生成方法の最大数
	static constexpr int TARGET_CREATE_PATTERN_MAX = static_cast<int>(TARGET_CREATE_PATTERN::MAX);

	// パラメータ
	ParameterEventTargetDestroy* parameterPtr_;

	// 制限時間
	float timeLimit_;

	// ターゲットらの生成
	void CreateTargets();

	// 状態別更新処理
	void UpdateChallenge() override;
	void UpdateEnd() override;

	// 状態線処理
	void ChangeStateChallenge() override;
	void ChangeStateEnd() override;
};

