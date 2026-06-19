#pragma once
#include <map>
#include <functional>
#include <vector>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2.h"
#include "Input.h"

class InputManager : public Singleton<InputManager>
{
	// シングルトンにだけ共有する
	friend class Singleton<InputManager>;

public:

	/// <summary>
	/// 入力状況の種類
	/// </summary>
	enum class TYPE
	{
		NONE,

		PLAYER_MOVE_RIGHT,		// 移動右
		PLAYER_MOVE_LEFT,		// 移動左
		PLAYER_MOVE_UP,			// 移動上
		PLAYER_MOVE_DOWN,		// 移動下
		PLAYER_ATTACK,			// 攻撃
		PLAYER_JUMP,			// ジャンプ
		PLAYER_DASH,			// ダッシュ
		PLAYER_RESPAWN,			// リスポーン
		PLAYER_GET_ITEM,		// アイテムを入手	

		CAMERA_MOVE_RIGHT,		// カメラ右移動
		CAMERA_MOVE_LEFT,		// カメラ左移動
		CAMERA_MOVE_UP,			// カメラ上移動
		CAMERA_MOVE_DOWN,		// カメラ下移動

		SELECT_RIGHT,			// 選択右
		SELECT_LEFT,			// 選択左
		SELECT_DOWN,			// 選択下
		SELECT_UP,				// 選択上
		SELECT_DECISION,		// 選択決定
		SELECT_CANCEL,			// 選択キャンセル

		PAUSE,					// ポーズ(開閉)

		DEBUG_SCENE_CHANGE,		// デバッグシーン遷移
		DEBUG_CAMERA_CHANGE,	// デバッグカメラビュー変更
		CREATE_POSITION,		// 位置リストの生成
		OPEN_FILE,				// ファイルを開く

		AVILITY_GRAVITY_RIGHT,	// 重力制御:右
		AVILITY_GRAVITY_LEFT,	// 重力制御:左
		AVILITY_GRAVITY_UP,		// 重力制御:上
		AVILITY_GRAVITY_DOWN,	// 重力制御:下

		AVILITY_STAMP,			// スタンプ
		AVILITY_STAMP_SUB,		// スタンプのサブ条件

		AVILITY_SHOT,			// ショット使用
		AVILITY_SHOT_SUB,		// ショットのサブ条件(使わない)
		AVILITY_SHOT_CHARGE,	// ショットチャージ
		AVILITY_SHOT_RIGHT,		// ショット方向決め右
		AVILITY_SHOT_LEFT,		// ショット方向決め左

		AVILITY_LASER,			// レーザー

		AVILITY_TELEPORT,		// テレポート
		AVILITY_TELEPORT_SUB,	// テレポートのサブ条件
		AVILITY_TELEPORT_HOLD,	// テレポートの保持

		SELECT_AVILITY_FIRST,	// アビリティの選択：１個目
		SELECT_AVILITY_SECOND,	// アビリティの選択：２個目
		SELECT_AVILITY_THIRD,	// アビリティの選択：３個目

		ACCEPT_NEW_PLAYER,		// 新規プレイヤー参加の受付
		ACCEPT_NEW_PLAYER_SUB,	// 新規プレイヤー参加の受付

		PLAYER_GAME_LEAVE,		// プレイヤーゲーム退出

		PLAYER_ENTER_DOOR,		// プレイヤーの入室

		SCENE_CHANGE,			// シーン遷移

		DEBUG_CREATE_ITEM_AVILITY,	// デバッグ用アビリティアイテム生成
		DEBUG_SELECT_RIGHT_ITEM_AVILITY,	// デバッグ用アビリティアイテム選択
		DEBUG_SELECT_LEFT_ITEM_AVILITY,	// デバッグ用アビリティアイテム選択
	};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// リソースの破棄
	/// </summary>
	void Release();

	/// <summary>
	/// 指定した状況での各入力機器の押下判定
	/// </summary>
	/// <param name="type">状況の種類</param>
	/// <param name="padNo">パッド番号(デフォルトはPAD1)</param>
	/// <returns>trueの場合入力中,falseの場合未入力</returns>
	bool IsNew(const TYPE type, const Input::JOYPAD_NO padNo = Input::JOYPAD_NO::PAD1);

	/// <summary>
	/// 指定した状況での各入力機器の押下判定(最初のみ)
	/// </summary>
	/// <param name="type">状況の種類</param>
	/// <param name="padNo">パッド番号(デフォルトはPAD1)</param>
	/// <returns>trueの場合入力中,falseの場合未入力</returns>
	bool IsTrgDown(const TYPE type, const Input::JOYPAD_NO padNo = Input::JOYPAD_NO::PAD1);

	/// <summary>
	/// 指定した状況での各入力機器の離した判定
	/// </summary>
	/// <param name="type">状況の種類</param>
	/// <param name="padNo">パッド番号(デフォルトはPAD1)</param>
	/// <returns>trueの場合離したタイミング,falseの場合まだ押下中</returns>
	bool IsTrgUp(const TYPE type, const Input::JOYPAD_NO padNo = Input::JOYPAD_NO::PAD1);

	/// <summary>
	/// マウス位置を設定
	/// </summary>
	/// <param name="pos"></param>
	void SetMousePos(const Vector2& pos);

	/// <summary>
	/// マウス座標の取得
	/// </summary>
	/// <returns>マウス座標の取得</returns>
	Vector2 GetMousePos() const;

	/// <summary>
	/// マウスの移動量を取得
	/// </summary>
	/// <param name=""></param>
	/// <returns>マウスの移動量</returns>
	Vector2 GetMouseMove() const;

	/// <summary>
	/// 左スティックの倒れた度合いを取得
	/// </summary>
	/// <param name="_no">パッド番号</param>
	/// <returns>倒れ具合を渡す</returns>
	Vector2 GetKnockLStickSize(Input::JOYPAD_NO no = Input::JOYPAD_NO::PAD1) const;
	
	/// <summary>
	/// 右スティックの倒れた度合いを取得
	/// </summary>
	/// <param name="_no">パッド番号</param>
	/// <returns>倒れた具合を渡す</returns>
	Vector2 GetKnockRStickSize(Input::JOYPAD_NO no = Input::JOYPAD_NO::PAD1) const;

private:

	// 入力トリガーの情報
	struct TriggerInfo
	{
		std::vector<int> keys;										// 入力に必要なキー(複数対応可能)
		std::vector<Input::JOYPAD_BTN> padButtons;					// 入力に必要なパッドボタン(複数対応可能)
		Input::JOYPAD_STICK padStick = Input::JOYPAD_STICK::MAX;	// 入力に必要なスティックの情報
		Input::MOUSE mouse = Input::MOUSE::MAX;						// 入力に必要なマウスの情報
		std::vector<TYPE> requiredTypes;							// 同時入力が必要な入力のもう一つの条件
		std::vector<TYPE> forbiddenTypes;							// 同時に入力の際に入力されてはならない条件
	};

	// 入力判定クラス
	std::unique_ptr<Input> input_;

	// 入力状況別のトリガーを管理するマップ
	std::map<TYPE, TriggerInfo> triggerMap_;

	// 入力状況に応じた押下処理を管理するマップ
	std::map<TYPE, std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>>> funcNewMap_;
	std::map<TYPE, std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>>> funcTrgDownMap_;
	std::map<TYPE, std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>>> funcTrgUpMap_;

	// 入力状況に応じたトリガーを登録
	void RegisterTrigger(
		const TYPE type, 
		const std::vector<int> keys,
		const std::vector<Input::JOYPAD_BTN> padButtons,
		const Input::JOYPAD_STICK padStick = Input::JOYPAD_STICK::MAX,
		const Input::MOUSE mouse = Input::MOUSE::MAX,
		const std::vector<TYPE> requiredTypes = {}, 
		const std::vector<TYPE> forbiddenTypes = {});

	// 処理の登録
	void RegisterTriggerFunction(
		const InputManager::TYPE type, 
		std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> newFuncs,
		std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> trgDownFuncs,
		std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> trgUpFuncs);

	// キー関係の入力判定
	bool IsNewKey(const TYPE type);
	bool IsTrgDownKey(const TYPE type);
	bool IsTrgUpKey(const TYPE type);

	// パッドボタンの入力判定
	bool IsNewPadButton(const TYPE type, const Input::JOYPAD_NO padNo);
	bool IsTrgDownPadButton(const TYPE type, const Input::JOYPAD_NO padNo);
	bool IsTrgUpPadButton(const TYPE type, const Input::JOYPAD_NO padNo);

	// パッドスティックの入力判定
	bool IsNewPadStick(const TYPE type, const Input::JOYPAD_NO padNo);
	bool IsTrgDownPadStick(const TYPE type, const Input::JOYPAD_NO padNo);
	bool IsTrgUpPadStick(const TYPE type, const Input::JOYPAD_NO padNo);

	// マウスの入力判定
	bool IsNewMouse(const TYPE type);
	bool IsTrgDownMouse(const TYPE type);
	bool IsTrgUpMouse(const TYPE type);

	// フィルター内の確認
	bool CheckFilter(const TYPE type, const Input::JOYPAD_NO padNo);

	// 長押し確認
	bool IsNewRaw(const TYPE type, const Input::JOYPAD_NO padNo);

	// コンストラクタ
	InputManager();

	// デストラクタ
	~InputManager();
};