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
	updateTypeMap_.emplace(TYPE::SCREEN, std::bind(&SceneSetting::UpdateTypeScreen, this));
	updateTypeMap_.emplace(TYPE::VOLUME_BGM, std::bind(&SceneSetting::UpdateTypeScreen, this));
	updateTypeMap_.emplace(TYPE::VOLUME_SE, std::bind(&SceneSetting::UpdateTypeScreen, this));
	updateTypeMap_.emplace(TYPE::ETC, std::bind(&SceneSetting::UpdateTypeEtc, this));
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
	}

	screenSprite_.handleIds = resMng_.GetHandles("screenMode");
	screenSprite_.index = isWindow_ ? 1 : 0;
	screenSprite_.pos = Vector2(868, 197);

	numberHandles_ = resMng_.GetHandles("numbers");
	volumeBgmPos_ = Vector2(878, 330);
	volumeSePos_ = Vector2(878, 410);
}

void SceneSetting::NormalUpdate()
{
	// 共通の選択処理
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DOWN, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, 1, 0, TYPE_MAX - 1);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_UP, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, -1, 0, TYPE_MAX - 1);
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
	// UIの描画
	for (auto& sprite : typeSprites_)
	{
		sprite.DrawRota();
	}

	// スクリーン選択の描画
	screenSprite_.index = isWindow_ ? 1 : 0;
	screenSprite_.DrawRota();

	// 数字の描画

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
		selectIndex_ = UtilityCommon::WrapStepIndex(volumeBgm_, 1, 0, SoundManager::MAX_BGM_VOLUME);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(volumeBgm_, -1, 0, SoundManager::MAX_BGM_VOLUME);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
}

void SceneSetting::UpdateTypeVolumeSe()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(volumeSe_, 1, 0, SoundManager::MAX_SE_VOLUME);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(volumeSe_, -1, 0, SoundManager::MAX_SE_VOLUME);
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
	sndMng_.PlaySe(SoundType::SE::SELECT);
}

void SceneSetting::Back()
{
	// 前のシーンに戻る
	scnMng_.PopScene();
	
	// 効果音再生
	sndMng_.PlaySe(SoundType::SE::CANCEL);
}

void SceneSetting::DrawNumber(const Vector2& pos, const int volume)
{
	//int numberSize = static_cast<int>();

	// 桁数取得
	//int digitCount = UtilityCommon::GetDigitCount(volume);

	//// 中央ぞろえ
	//Vector2 drawPos = {
	//	pos.x - 64 * digitCount / 2,
	//	pos.y - 64 * digitCount / 2
	//};

	//// 桁数分回す
	//for (int i = 0; i < digitCount; i++)
	//{
	//	// 描画する数字
	//	int index = 0;

	//	// 値の決定
	//	int divisor = 1;
	//	for (int j = 0; j < (digitCount - 1 - i); j++)
	//	{
	//		divisor *= 10;
	//	}
	//	index = (drawCount_ / divisor) % 10;

	//	// 描画
	//	DrawRotaGraph(
	//		drawPos.x + i * numberSize_.x,
	//		drawPos.y,
	//		numberScale_,
	//		0.0f,
	//		numberHandle_[index],
	//		true
	//	);
	//}
}
