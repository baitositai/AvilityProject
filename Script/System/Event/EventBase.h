#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "../../Common/Vector2F.h"
#include "../../Parameter/Event/ParameterEvent.h"

class ParameterEvent;
class SceneManager;
class SoundManager;
class EventManager;
class EnemyManager;
class GimmickManager;

class EventBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EventBase(std::unique_ptr<ParameterEvent> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EventBase();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// トリガー位置を設定
	/// </summary>
	/// <param name="triggerPos">トリガー座標</param>
	void SetTriggerPos(const Vector2F& triggerPos);

	/// <summary>
	/// イベントの削除判定
	/// </summary>
	/// <returns>削除判定</returns>
	const bool IsDelete() const { return isDelete_; }

protected:

	// カメラとの判定用
	static constexpr int OFFSET_X = 20;
	static constexpr int OFFSET_Y = 15;
	static constexpr int GROUND_OFFSET = 110;

	// 状態
	enum class STATE
	{
		START,			// 開始
		CHALLENGE,		// チャレンジ
		END,			// 終了
	};

	// イベントの削除判定
	bool isDelete_;

	// イベント発生トリガー位置
	Vector2F triggerPos_;

	// 状態
	STATE state_;

	// 状態別更新処理
	std::function<void()> update_;

	// 状態遷移管理マップ
	std::unordered_map<STATE, std::function<void()>> stateMap_;

	// パラメータ
	std::unique_ptr<ParameterEvent> parameter_;

	// 管理クラスの参照
	SceneManager& sceneManager_;
	EventManager& eventManager_;
	EnemyManager& enemyManager_;
	GimmickManager& gimmickManager_;
	SoundManager& soundManager_;

	// 型変換用のパラメータを返す関数
	ParameterEvent* GetParameterEventPtr() { return parameter_.get(); }

	// カメラを停止
	void CameraStop();

	// カメラ再スタート
	void CameraRestart();

	// 更新処理
	virtual void UpdateStart();
	virtual void UpdateChallenge();
	virtual void UpdateEnd();

	// 状態線処理
	void ChangeState(const STATE state);
	virtual void ChangeStateStart();
	virtual void ChangeStateChallenge();
	virtual void ChangeStateEnd();
};