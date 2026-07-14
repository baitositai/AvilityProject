#pragma once
#include <functional>
#include <unordered_map>
#include "../../Common/Vector2F.h"

class InputManager;
class SceneManager;

class Camera
{
public:

	// カメラの移動速度
	static constexpr float CAMERA_MOVE_SPEED = 5.0f;

	// スクロール速度
	static constexpr float SCROLL_SPEED = 0.8f;

	// カメラのモード
	enum class MODE
	{
		NONE,
		FREE,			// 自由移動
		FIXED_POINT,	// 固定点
		PLAYER_FOLLOW,	// プレイヤー追従
		CAMERA_SCROLL,	// カメラスクロール
		TRAIN_SHAKE		// 電車のような揺れ
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Camera();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Camera();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 停止
	/// </summary>
	void Stop() { isStop_ = true; }

	/// <summary>
	/// 再スタート
	/// </summary>
	void Restart() { isStop_ = false; }

	/// <summary>
	/// カメラモードの変更
	/// </summary>
	/// <param name="mode">変更先のモード</param>
	void ChangeMode(const MODE mode);

	/// <summary>
	/// カメラ位置を設定
	/// </summary>
	/// <param name="pos">カメラ位置</param>
	void SetCameraPos(const Vector2F& pos) { pos_ = pos; }

	/// <summary>
	/// カメラスクロールの移動量を格納
	/// </summary>
	/// <param name="scrollMoves">スクロール移動量</param>
	void SetCameraScrollMove(const std::vector<Vector2F> scrollMoves) { scrollMoves_ = scrollMoves; }

	/// <summary>
	/// 追従対象の座標を設定
	/// </summary>
	/// <param name="followPos">追従対象</param>
	void SetFollowPos(const Vector2F* followPos) { followPos_ = followPos; }

	/// <summary>
	/// カメラの移動制限を設定
	/// </summary>
	/// <param name="limitMin">移動最小値</param>
	/// <param name="limitMax">移動最大値</param>
	void SetCameraLimit(const Vector2F& limitMin, const Vector2F& limitMax) { limitMin_ = limitMin; limitMax_ = limitMax; }

	/// <summary>
	/// カメラシェイクの設定
	/// </summary>
	/// <param name="shakeTime">揺れる時間</param>
	/// <param name="shakePower">揺れの強さ</param>
	void SetCameraShake(const float shakeTime, const float shakePower);

	/// <summary>
	/// カメラ座標にオフセットを設定
	/// </summary>
	void SetCameraPosOffset();

	/// <summary>
	/// カメラ座標を戻す
	/// </summary>
	void ResetCameraPos();

	/// <summary>
	/// カメラ座標を返す
	/// </summary>
	/// <returns>カメラ座標</returns>
	const Vector2F& GetPos() const { return pos_; }

	/// <summary>
	/// 調整位置を返す
	/// </summary>
	/// <returns>調整位置</returns>
	const Vector2F& GetOffset() const { return offset_; }

	/// <summary>
	/// カメラモードを返す
	/// </summary>
	/// <returns>モードを返す</returns>
	const MODE GetMode() const { return mode_; }

	/// <summary>
	/// 停止判定を返す
	/// </summary>
	/// <returns>停止判定</returns>
	const bool IsStop() const { return isStop_; }

private:

	// 揺れ時間
	float shakeTime_;

	// 電車用揺れ時間
	float shakeTrainTime_;

	// 揺れの強さ
	float shakePower_;

	// 停止判定
	bool isStop_;

	// オフセット
	Vector2F offset_;

	// 入力管理クラス
	InputManager& inputMng_;

	// シーン管理クラス
	SceneManager& scnMng_;

	// 追従対象
	const Vector2F* followPos_;

	// カメラの座標
	Vector2F pos_;

	// カメラの移動制限の範囲
	Vector2F limitMin_;
	Vector2F limitMax_;

	// カメラのモード
	MODE mode_;

	// 状態遷移処理
	std::function<void()> updateFunction_;

	// スクロール量の保持
	std::vector<Vector2F> scrollMoves_;

	// モード別更新処理
	std::unordered_map<MODE, std::function<void()>> changeStateMap_;

	// モード別更新処理
	void UpdateModeFree();
	void UpdateModeFixedPoint();
	void UpdateModePlayerFollow();
	void UpdateModeScroll();
	void UpdateModeTrainShake();

	// モード別遷移処理
	void ChangeModeFree();
	void ChangeModeFixedPoint();
	void ChangeModePlayerFollow();
	void ChangeModeScroll();
	void ChangeModeTrainShake();

	// カメラシェイク処理
	void CameraShake();

	// カメラの移動制限
	void LimitCameraMove();
};