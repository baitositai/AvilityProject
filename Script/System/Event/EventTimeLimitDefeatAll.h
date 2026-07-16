#pragma once
#include <vector>
#include "EventBase.h"
#include "../../Common/Vector2.h"
#include "../../Manager/Game/EnemyTypes.h"
#include "../../Parameter/Event/ParameterEventTimeLimitDefeatAll.h"

class ParameterEventTimeLimitDefeatAll;

class EventTimeLimitDefeatAll : public EventBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EventTimeLimitDefeatAll(std::unique_ptr<ParameterEventTimeLimitDefeatAll> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EventTimeLimitDefeatAll() override;

private:

	// 敵の生成方法
	enum class ENEMY_CREATE_TYPE
	{
		FIX,
		RANDOM,
		MAX
	};	
	
	// 生成方法の最大数
	static constexpr int ENEMY_CREATE_TYPE_MAX = static_cast<int>(ENEMY_CREATE_TYPE::MAX);

	// 名前の省略形
	using ETYPE = EnemyTypes::TYPE;

	// パラメータ
	ParameterEventTimeLimitDefeatAll* parameterPtr_;

	// 敵の生成リスト
	std::list<std::vector<ETYPE>> createEnemiesList_;

	// 敵の生成リストの生成
	void CreateEnemyList();

	// 敵の生成
	void CreateEnemies();

	// 状態別更新処理
	void UpdateChallenge() override;
	void UpdateEnd() override;

	// 状態線処理
	void ChangeStateChallenge() override;
	void ChangeStateEnd() override;
};