#include <DxLib.h>
#include "InputManager.h"

void InputManager::Init()
{
	// 入力判定処理の生成と初期化
	input_ = std::make_unique<Input>();
	input_->Init();

	// 入力状況に応じたトリガーの登録
	using BTN = Input::JOYPAD_BTN;
	using STICK = Input::JOYPAD_STICK;
	using MOUSE = Input::MOUSE;

	// プレイヤー操作
	RegisterTrigger(TYPE::PLAYER_MOVE_RIGHT, { KEY_INPUT_D }, { }, STICK::L_STICK_RIGHT);
	RegisterTrigger(TYPE::PLAYER_MOVE_LEFT, { KEY_INPUT_A }, { }, STICK::L_STICK_LEFT);
	RegisterTrigger(TYPE::PLAYER_MOVE_UP, { KEY_INPUT_W }, { }, STICK::L_STICK_UP);
	RegisterTrigger(TYPE::PLAYER_MOVE_DOWN, { KEY_INPUT_S }, { }, STICK::L_STICK_DOWN);

	// リスポーン
	RegisterTrigger(TYPE::PLAYER_RESPAWN, { KEY_INPUT_RETURN }, { BTN::RB_RIGHT });

	// ジャンプ
	RegisterTrigger(TYPE::PLAYER_JUMP, { KEY_INPUT_SPACE }, { BTN::RB_RIGHT }, STICK::MAX, MOUSE::MAX, {}, { });

	// ダッシュ
	RegisterTrigger(TYPE::PLAYER_DASH, { KEY_INPUT_LSHIFT }, { BTN::RB_DOWN });

	// 通常攻撃
	RegisterTrigger(TYPE::PLAYER_ATTACK, { KEY_INPUT_R }, { BTN::RB_LEFT });

	// アイテム入手
	RegisterTrigger(TYPE::PLAYER_GET_ITEM, { KEY_INPUT_SPACE }, { BTN::RB_DOWN });

	// アイテムを投げる
	RegisterTrigger(TYPE::PLAYER_THROW_ITEM, { KEY_INPUT_Q }, { BTN::R_BUTTON, BTN::R_TRIGGER });

	// アビリティ：重力方向の切り替え
	RegisterTrigger(TYPE::AVILITY_GRAVITY_RIGHT, { KEY_INPUT_RIGHT }, { }, STICK::R_STICK_RIGHT);
	RegisterTrigger(TYPE::AVILITY_GRAVITY_LEFT, { KEY_INPUT_LEFT }, { }, STICK::R_STICK_LEFT);
	RegisterTrigger(TYPE::AVILITY_GRAVITY_UP, { KEY_INPUT_UP }, { }, STICK::R_STICK_UP);
	RegisterTrigger(TYPE::AVILITY_GRAVITY_DOWN, { KEY_INPUT_DOWN }, { }, STICK::R_STICK_DOWN);
	
	// アビリティ：ショット
	RegisterTrigger(TYPE::AVILITY_SHOT, { KEY_INPUT_E }, { BTN::RB_TOP }, STICK::MAX, MOUSE::MAX, { TYPE::AVILITY_SHOT_SUB });
	RegisterTrigger(TYPE::AVILITY_SHOT_SUB, { KEY_INPUT_S }, { }, STICK::L_STICK_DOWN);
	RegisterTrigger(TYPE::AVILITY_SHOT_CHARGE, { KEY_INPUT_E }, { BTN::RB_TOP });
	RegisterTrigger(TYPE::AVILITY_SHOT_RIGHT, { KEY_INPUT_RIGHT }, {}, STICK::MAX);
	RegisterTrigger(TYPE::AVILITY_SHOT_LEFT, { KEY_INPUT_LEFT }, {}, STICK::MAX);
	
	// アビリティ：スタンプ
	RegisterTrigger(TYPE::AVILITY_STAMP, { KEY_INPUT_SPACE }, { BTN::RB_RIGHT }, STICK::MAX, MOUSE::MAX, { TYPE::AVILITY_STAMP_SUB });
	RegisterTrigger(TYPE::AVILITY_STAMP_SUB, { KEY_INPUT_S }, { }, STICK::L_STICK_DOWN);

	// アビリティ：レーザー
	RegisterTrigger(TYPE::AVILITY_LASER, { KEY_INPUT_E }, { BTN::RB_TOP }, STICK::MAX, MOUSE::MAX, {}, { TYPE::AVILITY_SHOT_SUB, TYPE::AVILITY_TELEPORT_SUB });

	// アビリティ：テレポート
	RegisterTrigger(TYPE::AVILITY_TELEPORT, { KEY_INPUT_E }, { BTN::RB_TOP }, STICK::MAX, MOUSE::MAX, { TYPE::AVILITY_TELEPORT_SUB });
	RegisterTrigger(TYPE::AVILITY_TELEPORT_SUB, { KEY_INPUT_W }, { }, STICK::L_STICK_UP);
	RegisterTrigger(TYPE::AVILITY_TELEPORT_HOLD, { KEY_INPUT_E }, { BTN::RB_TOP });

	// アビリティの選択
	RegisterTrigger(TYPE::SELECT_AVILITY_FIRST, { KEY_INPUT_LEFT }, { BTN::LB_LEFT }, STICK::R_STICK_LEFT );
	RegisterTrigger(TYPE::SELECT_AVILITY_SECOND, { KEY_INPUT_UP }, { BTN::LB_TOP }, STICK::R_STICK_UP);
	RegisterTrigger(TYPE::SELECT_AVILITY_THIRD, { KEY_INPUT_RIGHT }, { BTN::LB_RIGHT }, STICK::R_STICK_RIGHT);

	// カメラ制御
	RegisterTrigger(TYPE::CAMERA_MOVE_RIGHT, { KEY_INPUT_RIGHT }, { }, STICK::R_STICK_RIGHT);
	RegisterTrigger(TYPE::CAMERA_MOVE_LEFT, { KEY_INPUT_LEFT }, { }, STICK::R_STICK_LEFT);
	RegisterTrigger(TYPE::CAMERA_MOVE_UP, { KEY_INPUT_UP }, { }, STICK::R_STICK_UP);
	RegisterTrigger(TYPE::CAMERA_MOVE_DOWN, { KEY_INPUT_DOWN }, { }, STICK::R_STICK_DOWN);

	// メニュー操作
	RegisterTrigger(TYPE::SELECT_RIGHT, { KEY_INPUT_D }, { }, STICK::L_STICK_RIGHT);
	RegisterTrigger(TYPE::SELECT_LEFT, { KEY_INPUT_A }, { }, STICK::L_STICK_LEFT);
	RegisterTrigger(TYPE::SELECT_UP, { KEY_INPUT_W }, { }, STICK::L_STICK_UP);
	RegisterTrigger(TYPE::SELECT_DOWN, { KEY_INPUT_S }, { }, STICK::L_STICK_DOWN);
	RegisterTrigger(TYPE::SELECT_DECISION, { KEY_INPUT_SPACE }, { BTN::RB_RIGHT }, STICK::MAX/*, MOUSE::CLICK_LEFT*/);
	RegisterTrigger(TYPE::SELECT_CANCEL, { KEY_INPUT_BACK }, { BTN::RB_DOWN });
	RegisterTrigger(TYPE::PAUSE, { KEY_INPUT_BACK }, { BTN::SELECT });

	// 新規プレイヤー参加
	RegisterTrigger(TYPE::ACCEPT_NEW_PLAYER, { }, { BTN::RB_RIGHT }, STICK::MAX, MOUSE::MAX, { TYPE::ACCEPT_NEW_PLAYER_SUB });
	RegisterTrigger(TYPE::ACCEPT_NEW_PLAYER_SUB, { }, { BTN::RB_DOWN });

	// 追加プレイヤーの途中離脱機能
	RegisterTrigger(TYPE::PLAYER_GAME_LEAVE, { }, { BTN::START });

	// 入室
	RegisterTrigger(TYPE::PLAYER_ENTER_DOOR, { KEY_INPUT_W }, { }, STICK::L_STICK_UP);

	// シーン遷移
	RegisterTrigger(TYPE::SCENE_CHANGE, { KEY_INPUT_SPACE }, { BTN::RB_RIGHT, BTN::START });

	// ボス選択
	RegisterTrigger(TYPE::BOSS_SELECT_LEFT, { KEY_INPUT_LEFT }, { BTN::LB_LEFT });
	RegisterTrigger(TYPE::BOSS_SELECT_RIGHT, { KEY_INPUT_RIGHT }, { BTN::LB_RIGHT });

	// デバッグ操作
	RegisterTrigger(TYPE::DEBUG_SCENE_CHANGE, { KEY_INPUT_RSHIFT }, { });
	RegisterTrigger(TYPE::DEBUG_CAMERA_CHANGE, { KEY_INPUT_TAB }, { });
	RegisterTrigger(TYPE::CREATE_POSITION, { KEY_INPUT_C }, { });
	RegisterTrigger(TYPE::OPEN_FILE, { KEY_INPUT_V }, { });

	// デバッグ用アビリティアイテム生成
	RegisterTrigger(TYPE::DEBUG_CREATE_ITEM_AVILITY, { KEY_INPUT_1 }, { BTN::LB_DOWN });
	RegisterTrigger(TYPE::DEBUG_SELECT_LEFT_ITEM_AVILITY, { KEY_INPUT_2 }, { BTN::LB_LEFT });
	RegisterTrigger(TYPE::DEBUG_SELECT_RIGHT_ITEM_AVILITY, { KEY_INPUT_3 }, { BTN::LB_RIGHT });
}

void InputManager::Update()
{
	input_->Update();
}

void InputManager::Release()
{
	triggerMap_.clear();
	funcNewMap_.clear();
	funcTrgDownMap_.clear();
	funcTrgUpMap_.clear();
	input_->Release();
}

bool InputManager::IsNew(const TYPE type, const Input::JOYPAD_NO padNo)
{
	bool isBaseActive = false;
	for (auto& func : funcNewMap_[type])
	{
		if (func(type, padNo))
		{
			isBaseActive = true;
			break;
		}
	}

	if (!isBaseActive)
	{
		return false;
	}

	return CheckFilter(type, padNo);
}

bool InputManager::IsTrgDown(const TYPE type, const Input::JOYPAD_NO padNo)
{
	bool isBaseActive = false;
	for (auto& func : funcTrgDownMap_[type])
	{
		if (func(type, padNo))
		{
			isBaseActive = true;
			break;
		}
	}

	if (!isBaseActive)
	{
		return false;
	}

	return CheckFilter(type, padNo);
}

bool InputManager::IsTrgUp(const TYPE type, const Input::JOYPAD_NO padNo)
{
	bool isBaseActive = false;
	for (auto& func : funcTrgUpMap_[type])
	{
		if (func(type, padNo))
		{
			isBaseActive = true;
			break;
		}
	}

	if (!isBaseActive)
	{
		return false;
	}

	return CheckFilter(type, padNo);
}

void InputManager::SetMousePos(const Vector2& pos)
{
	input_->SetMousePos(pos);
}

Vector2 InputManager::GetMousePos() const
{
	return input_->GetMousePos();
}

Vector2 InputManager::GetMouseMove() const
{
	return input_->GetMousePosDistance();
}

Vector2 InputManager::GetKnockLStickSize(Input::JOYPAD_NO no) const
{
	auto padInfo = input_->GetJPadInputState(no);
	return Vector2(padInfo.AKeyLX, padInfo.AKeyLY);
}

Vector2 InputManager::GetKnockRStickSize(Input::JOYPAD_NO no) const
{
	auto padInfo = input_->GetJPadInputState(no);
	return Vector2(padInfo.AKeyRX, padInfo.AKeyRY);
}

void InputManager::RegisterTrigger(const TYPE type, const std::vector<int> keys, const std::vector<Input::JOYPAD_BTN> padButtons, const Input::JOYPAD_STICK padStick, const Input::MOUSE mouse, const std::vector<TYPE> requiredTypes, const std::vector<TYPE> forbiddenTypes)
{
	// トリガーの情報を設定
	TriggerInfo info = { keys, padButtons, padStick, mouse, requiredTypes, forbiddenTypes };

	// 情報の格納
	triggerMap_[type] = info;

	// 各種処理の配列
	std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> newFuncs;
	std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> isTrgDownFuncs;
	std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> isTrgUpFuncs;

	// キーが登録されている場合
	if (!info.keys.empty())
	{
		newFuncs.push_back([this](TYPE t, Input::JOYPAD_NO) { return IsNewKey(t); });
		isTrgDownFuncs.push_back([this](TYPE t, Input::JOYPAD_NO) { return IsTrgDownKey(t); });
		isTrgUpFuncs.push_back([this](TYPE t, Input::JOYPAD_NO) { return IsTrgUpKey(t); });

	}
	// パッドのボタンが登録されている場合
	if (!info.padButtons.empty())
	{
		newFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsNewPadButton(t, padNo); });
		isTrgDownFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsTrgDownPadButton(t, padNo); });
		isTrgUpFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsTrgUpPadButton(t, padNo); });
	}
	// パッドのスティックが登録されている場合
	if (info.padStick != Input::JOYPAD_STICK::MAX)
	{
		newFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsNewPadStick(t, padNo); });
		isTrgDownFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsTrgDownPadStick(t, padNo); });
		isTrgUpFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsTrgUpPadStick(t, padNo); });
	}
	// マウスの登録がされている場合
	if (info.mouse != Input::MOUSE::MAX)
	{
		newFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsNewMouse(t); });
		isTrgDownFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsTrgDownMouse(t); });
		isTrgUpFuncs.push_back([this](TYPE t, Input::JOYPAD_NO padNo) { return IsTrgUpMouse(t); });
	}

	// 処理の登録
	RegisterTriggerFunction(type, newFuncs, isTrgDownFuncs, isTrgUpFuncs);
}

void InputManager::RegisterTriggerFunction(const TYPE type, std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> newFuncs, std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> trgDownFuncs, std::vector<std::function<bool(TYPE, Input::JOYPAD_NO)>> trgUpFuncs)
{
	funcNewMap_.emplace(type, newFuncs);
	funcTrgDownMap_.emplace(type, trgDownFuncs);
	funcTrgUpMap_.emplace(type, trgUpFuncs);
}

bool InputManager::IsNewKey(const TYPE type)
{
	for (int key : triggerMap_[type].keys)
	{
		if (input_->IsNew(key))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsTrgDownKey(const TYPE type)
{
	for (int key : triggerMap_[type].keys)
	{
		if (input_->IsTrgDown(key))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsTrgUpKey(const TYPE type)
{
	for (int key : triggerMap_[type].keys)
	{
		if (input_->IsTrgUp(key))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsNewPadButton(const TYPE type, const Input::JOYPAD_NO padNo)
{
	for (auto button : triggerMap_[type].padButtons)
	{
		if (input_->IsPadBtnNew(padNo, button))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsTrgDownPadButton(const TYPE type, const Input::JOYPAD_NO padNo)
{
	for (auto button : triggerMap_[type].padButtons)
	{
		if (input_->IsPadBtnTrgDown(padNo, button))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsTrgUpPadButton(const TYPE type, const Input::JOYPAD_NO padNo)
{
	for (auto button : triggerMap_[type].padButtons)
	{
		if (input_->IsPadBtnTrgUp(padNo, button))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsNewPadStick(const TYPE type, const Input::JOYPAD_NO padNo)
{
	return input_->IsStickNew(padNo, triggerMap_[type].padStick);
}

bool InputManager::IsTrgDownPadStick(const TYPE type, const Input::JOYPAD_NO padNo)
{
	return input_->IsStickDown(padNo, triggerMap_[type].padStick);
}

bool InputManager::IsTrgUpPadStick(const TYPE type, const Input::JOYPAD_NO padNo)
{
	return input_->IsStickUp(padNo, triggerMap_[type].padStick);
}

bool InputManager::IsNewMouse(const TYPE type)
{
	return input_->IsMouseNew(triggerMap_[type].mouse);
}

bool InputManager::IsTrgDownMouse(const TYPE type)
{
	return input_->IsMouseTrgDown(triggerMap_[type].mouse);
}

bool InputManager::IsTrgUpMouse(const TYPE type)
{
	return input_->IsMouseTrgUp(triggerMap_[type].mouse);
}

bool InputManager::CheckFilter(const TYPE type, const Input::JOYPAD_NO padNo)
{
	const auto& info = triggerMap_[type];

	// 同時に押されていなければならないTYPEのチェック
	for (const auto& reqType : info.requiredTypes)
	{
		if (!IsNewRaw(reqType, padNo))
		{
			return false;
		}
	}

	// 同時に押されていてはならないTYPEのチェック
	for (const auto& forbType : info.forbiddenTypes)
	{
		if (IsNewRaw(forbType, padNo))
		{
			return false;
		}
	}

	return true;
}

bool InputManager::IsNewRaw(const TYPE type, const Input::JOYPAD_NO padNo)
{
	for (auto& func : funcNewMap_[type])
	{
		if (func(type, padNo))
		{
			return true;
		}
	}
	return false;
}

InputManager::InputManager()
{
	input_ = nullptr;
	triggerMap_.clear();
	funcNewMap_.clear();
	funcTrgDownMap_.clear();
	funcTrgUpMap_.clear();
}

InputManager::~InputManager()
{

}