#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "../../Common/Vector2F.h"
#include "../../Parameter/Event/ParameterEvent.h"
#include "../../Manager/Game/EventTypes.h"

class ParameterEvent;
class SceneManager;
class SoundManager;
class EventManager;
class EnemyManager;
class GimmickManager;
class UiManager;

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

	/// <summary>
	/// UIの削除判定
	/// </summary>
	/// <returns>UIの削除判定</returns>
	const bool IsDeleteUi() const { return isDeleteUi_; }

	/// <summary>
	/// 時間を返す
	/// </summary>
	/// <returns>時間</returns>
	const float GetTimer() const { return timeLimit_; }

	/// <summary>
	/// イベント種類を返す
	/// </summary>
	/// <returns>イベント種類</returns>
	const EventTypes::TYPE GetType() const { return eventType_; }

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

	// 制限時間
	float timeLimit_;

	// イベントの削除判定
	bool isDelete_;

	// UIの削除判定
	bool isDeleteUi_;

	// イベントの種類
	EventTypes::TYPE eventType_;

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
	UiManager& uiManager_;

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

	// UIの生成
	void CreateUi();
};