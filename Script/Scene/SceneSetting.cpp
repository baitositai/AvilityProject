#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/SoundType.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Utility/UtilityCommon.h"
#include "SceneSetting.h"

SceneSetting::SceneSetting() :
	application_(Application::GetInstance())
{
	// 処理の登録
	updateTypeMap_.emplace(TYPE::SCREEN, std::bind(&SceneSetting::UpdateTypeScreen, this));
	updateTypeMap_.emplace(TYPE::VOLUME_BGM, std::bind(&SceneSetting::UpdateTypeVolumeBgm, this));
	updateTypeMap_.emplace(TYPE::VOLUME_SE, std::bind(&SceneSetting::UpdateTypeVolumeSe, this));
	updateTypeMap_.emplace(TYPE::BACK, std::bind(&SceneSetting::UpdateTypeEtc, this));
	updateTypeMap_.emplace(TYPE::APPLY, std::bind(&SceneSetting::UpdateTypeEtc, this));
	updataFunc_ = std::bind(&SceneSetting::NormalUpdate, this);
	drawFunc_ = std::bind(&SceneSetting::NormalDraw, this);

	// 初期化
	numberScale_ = 0.0f;
	numberHandles_ = nullptr;
	selectIndex_ = -1;
	selectType_ = -1;
	volumeBgm_ = -1;
	volumeSe_ = -1;
	volumeBgmPos_ = Vector2(0, 0);
	volumeSePos_ = Vector2(0, 0);
	isWindow_ = false;
	isBack_ = false;
	padNo_ = Input::JOYPAD_NO::PAD1;
}

SceneSetting::~SceneSetting()
{
}

void SceneSetting::Init()
{
	// 初期状態の取得
	volumeBgm_ = sndMng_.GetBgmVolume();
	volumeSe_ = sndMng_.GetSeVolume();
	isWindow_ = application_.GetWindowMode();

	// リソースの設定
	int index = 0;
	std::vector<Vector2> posList = {
		Vector2(356, 197),
		Vector2(356, 330),
		Vector2(356, 410),
		Vector2(211, 650),
		Vector2(1290, 650)
	};
	for (auto& sprite : typeSprites_)
	{
		sprite.handleIds = resMng_.GetHandles("settings");
		sprite.index = index;
		sprite.pos = posList[index];
		index++;
	}

	screenSprite_.handleIds = resMng_.GetHandles("screenMode");
	screenSprite_.index = isWindow_ ? 1 : 0;
	screenSprite_.pos = Vector2(868, 197);

	numberHandles_ = resMng_.GetHandles("numbers");
	volumeBgmPos_ = Vector2(878, 330);
	volumeSePos_ = Vector2(878, 410);

	// 選択番号初期化
	selectIndex_ = 0;
	selectType_ = 0;
	numberScale_ = 0.5f;
}

void SceneSetting::NormalUpdate()
{
	// 共通の選択処理
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DOWN, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, 1, 0, SLECT_MAX);
		selectType_ = selectIndex_;
		isBack_ = selectType_ == static_cast<int>(TYPE::BACK);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_UP, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, -1, 0, SLECT_MAX);
		selectType_ = selectIndex_;
		isBack_ = selectType_ == static_cast<int>(TYPE::BACK);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_CANCEL, padNo_))
	{
		Back();
		return;
	}

	// 種類別処理
	updateTypeMap_[static_cast<TYPE>(selectIndex_)]();
}

void SceneSetting::NormalDraw()
{
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, UtilityCommon::BLACK, true);


	// UIの描画
	for (int i = 0; i < TYPE_MAX; i++)
	{
		if (i == selectType_)
		{
			// 画面を赤くする
			SetDrawAddColor(0, -255, -255);
		}

		typeSprites_[i].DrawRota();

		// スクリーン選択の描画
		if (i == static_cast<int>(TYPE::SCREEN))
		{		
			screenSprite_.index = isWindow_ ? 1 : 0;
			screenSprite_.DrawRota();
		}
		else if(i == static_cast<int>(TYPE::VOLUME_BGM))
		{
			DrawNumber(volumeBgmPos_, volumeBgm_);
		}
		else if(i == static_cast<int>(TYPE::VOLUME_SE))
		{
			DrawNumber(volumeSePos_, volumeSe_);
		}

		SetDrawAddColor(0, 0, 0);
	}
}

void SceneSetting::UpdateTypeScreen()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT, padNo_) ||
		inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		sndMng_.PlaySe(SoundType::SE::SELECT);
		isWindow_ = !isWindow_;
		return;
	}
}

void SceneSetting::UpdateTypeVolumeBgm()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT, padNo_))
	{
		volumeBgm_ = UtilityCommon::WrapStepIndex(volumeBgm_, 1, 0, SoundManager::MAX_BGM_VOLUME);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		volumeBgm_ = UtilityCommon::WrapStepIndex(volumeBgm_, -1, 0, SoundManager::MAX_BGM_VOLUME);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
}

void SceneSetting::UpdateTypeVolumeSe()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT, padNo_))
	{
		volumeSe_ = UtilityCommon::WrapStepIndex(volumeSe_, 1, 0, SoundManager::MAX_SE_VOLUME);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		volumeSe_ = UtilityCommon::WrapStepIndex(volumeSe_, -1, 0, SoundManager::MAX_SE_VOLUME);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
}

void SceneSetting::UpdateTypeEtc()
{
	// 項目を選択
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT, padNo_) ||
		inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		sndMng_.PlaySe(SoundType::SE::SELECT);
		isBack_ = !isBack_;
		selectType_ = isBack_ ? static_cast<int>(TYPE::BACK) : static_cast<int>(TYPE::APPLY);
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DECISION, padNo_))
	{
		// 選択別に処理
		isBack_ ? Back() : Apply();
	}
}

void SceneSetting::Apply()
{
	// スクリーンモードの設定
	application_.SetWindowMode(isWindow_);

	// 音量の反映
	sndMng_.SetDefaultVolumeBgm(volumeBgm_);
	sndMng_.SetDefaultVolumeSe(volumeSe_);

	// 効果音再生
	sndMng_.PlaySe(SoundType::SE::DECISION);
}

void SceneSetting::Back()
{
	// 効果音再生
	sndMng_.PlaySe(SoundType::SE::CANCEL);

	// 前のシーンに戻る
	scnMng_.PopScene();
}

void SceneSetting::DrawNumber(const Vector2& pos, const int volume)
{
	// サイズの設定
	constexpr float DEFAULT_NUMBER_SIZE = 128.0f;
	const int numberSize = static_cast<int>(DEFAULT_NUMBER_SIZE * numberScale_);

	// 桁数取得
	const int digitCount = UtilityCommon::GetDigitCount(volume);

	// 中央ぞろえ
	Vector2 drawPos = {
		pos.x - numberSize * digitCount / 2,
		pos.y
	};

	// 桁数分回す
	for (int i = 0; i < digitCount; i++)
	{
		// 描画する数字
		int index = 0;

		// 値の決定
		int divisor = 1;
		for (int j = 0; j < (digitCount - 1 - i); j++)
		{
			divisor *= 10;
		}
		index = (volume / divisor) % 10;

		// 描画
		DrawRotaGraph(
			drawPos.x + i * numberSize,
			drawPos.y,
			numberScale_,
			0.0f,
			numberHandles_[index],
			true
		);
	}
}
