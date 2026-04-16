#pragma once
#include <functional>
#include <unordered_map>
#include "../ActorBase.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"

class ComponentBase;

class CharacterBase : public ActorBase
{
public:
	
	// キャラクターの共通パラメータ
	struct Parameter : public ActorBase::Parameter
	{
		int hp = -1;				// 体力
		int attackPower = -1;		// 攻撃力
	};

	// キャラクター共通の状態
	enum class STATE
	{
		RESPAWN,	// 復活
		ALIVE,		// 生存
		DEAD,		// 死亡
		MAX
	};
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="componentNameList">コンポーネント生成用名前リスト</param>
	CharacterBase(Parameter* parameter, const std::vector<std::string> componentNameList);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CharacterBase() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	virtual void DebugDraw() override;

	/// <summary>
	/// 状態遷移処理
	/// </summary>
	/// <param name="state">状態</param>
	void ChangeState(const STATE state);

protected:	
	
	// キャラクターの状態
	STATE state_;

private:		
	
	// キャラクターのパラメータ
	Parameter* characterParameterPtr_;	

	// 状態別更新処理
	std::function<void()> updateStateFunction_;

	// 状態遷移管理マップ
	std::unordered_map<STATE, std::function<void()>> stateChangeMap_;

	// 状態別遷移処理
	void ChangeStateRespawn();
	void ChangeStateAlive();
	void ChangeStateDead();

	// 状態別更新処理
	void UpdateStateRespawn();
	void UpdateStateAlive();
	void UpdateStateDead();
};

