#pragma once
#include <functional>
#include <unordered_map>
#include "../../Common/Vector2F.h"

class InputManager;

class Camera
{
public:

	// カメラのモード
	enum class MODE
	{
		NONE,
		FREE,			// 自由移動
		FIXED_POINT,	// 固定点
		PLAYER_FOLLOW,	// プレイヤー追従
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
	/// カメラの移動制限を設定
	/// </summary>
	/// <param name="limitMin">移動最小値</param>
	/// <param name="limitMax">移動最大値</param>
	void SetCameraLimit(const Vector2F& limitMin, const Vector2F& limitMax) { limitMin_ = limitMin; limitMax_ = limitMax; }

	/// <summary>
	/// カメラ座標を返す
	/// </summary>
	/// <returns>カメラ座標</returns>
	const Vector2F& GetPos() const { return pos_; }

	/// <summary>
	/// カメラモードを返す
	/// </summary>
	/// <returns>モードを返す</returns>
	const MODE GetMode() const { return mode_; }

private:

	// カメラの移動速度
	static constexpr float CAMERA_MOVE_SPEED = 5.0f;

	// 入力管理クラス
	InputManager& inputMng_;

	// カメラの座標
	Vector2F pos_;

	// カメラの移動制限の範囲
	Vector2F limitMin_;
	Vector2F limitMax_;

	// カメラのモード
	MODE mode_;

	// 状態遷移処理
	std::function<void()> updateFunction_;

	// モード別更新処理
	std::unordered_map<MODE, std::function<void()>> changeStateMap_;

	// モード別更新処理
	void UpdateModeFree();
	void UpdateModeFixedPoint();
	void UpdateModePlayerFollow();

	// モード別遷移処理
	void ChangeModeFree();
	void ChangeModeFixedPoint();
	void ChangeModePlayerFollow();

	// カメラの移動制限
	void LimitCameraMove();
};