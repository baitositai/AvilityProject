#include <DxLib.h>
#include <cassert>
#include "../../Resource/ResourceSound.h"
#include "ResourceManager.h"
#include "SoundManager.h"

// 音源種類の省略形
using TYPE = SoundType::TYPE;
using BGM = SoundType::BGM;
using SE = SoundType::SE;

void SoundManager::SceneChangeResources()
{
	// 空じゃない場合
	if (!loadedBgmMap_.empty()) { loadedBgmMap_.clear(); }
	if (!loadedSeMap_.empty()) { loadedSeMap_.clear(); }

	// 一時マップ
	std::unordered_map<BGM, SoundData> tempBgmMap;
	std::unordered_map<SE, SoundData> tempSeMap;

	// シーン用リソースを取得
	std::unordered_map<std::string, ResourceSound*> resourceMap = resourceManager_.GetSceneSounds();

	// リソースが空の場合は終了
	if (resourceMap.empty())
	{
		return;
	}

	// 新規リソースを追加
	for (auto it = resourceMap.begin(); it != resourceMap.end(); )
	{
		// 追加処理
		Add(it->first, it->second);

		// 次へ
		++it;
	}

	// 再生しているBGMをクリア
	playingBgmList_.clear();
}

void SoundManager::Update()
{
	// 空の場合は処理を行わない
	if (fadeSeMap_.empty())
	{
		return;
	}

	for (auto it = fadeSeMap_.begin(); it != fadeSeMap_.end(); )
	{
		// 各種情報の取得・定義
		const SE key = it->first;		// キー
		FadeData& data = it->second;	// フェードデータ
		bool erased = false;			// 削除判定

		// フェードイン処理
		if (data.fadeType == FADE::FADE_IN)
		{
			// 音量増加
			data.soundData.volume += MAX / defaultVolumeSe_;

			// 最大音量に達した場合
			if (data.soundData.volume >= data.goalVolume)
			{
				data.soundData.volume = data.goalVolume;	// 最大音量に設定
				it = fadeSeMap_.erase(it);					// マップ内から削除
				erased = true;								// 削除判定をtrueに
			}
		}
		// フェードアウト処理
		else if (data.fadeType == FADE::FADE_OUT)
		{
			// 音量減少
			data.soundData.volume -= MAX / defaultVolumeSe_;

			// 音量が0以下になる場合
			if (data.soundData.volume <= 0)
			{
				data.soundData.volume = 0;		// 音量を0に設定
				it = fadeSeMap_.erase(it);		// マップ内から削除
				erased = true;					// 削除判定をtrueに
			}
		}

		// 削除判定が出ていない場合
		if (!erased)
		{
			// 音量変更
			ChangeVolumeSe(data.soundData.volume, key);
			++it;
		}
	}
}

void SoundManager::PlayBgm(const SoundType::BGM key, const bool topPos, const int volume)
{
	//音源があるか確認
	auto it = loadedBgmMap_.find(key);

	//音源がない場合
	if (it == loadedBgmMap_.end())
	{
		// stringキーを取得
		const std::string stringKey = SoundType::GetStringFromBGM(key);

		// サウンドを取得して読み込み処理
		auto sound = resourceManager_.GetResourceSound(stringKey);
		resourceManager_.GetHandle(stringKey);

		// サウンドの管理マップに登録
		Add(stringKey, sound);
	}

	// 音量調整
	loadedBgmMap_[key].volume = defaultVolumeBgm_;
	ChangeVolumeBgm(defaultVolumeBgm_, key);

	//再生
	PlaySoundMem(loadedBgmMap_[key].handle, loadedBgmMap_[key].playType, topPos);

	// リストに追加
	playingBgmList_.push_back(key);
}

void SoundManager::PlaySe(const SoundType::SE key, const bool topPos, const int volume)
{
	//音源があるか確認
	auto it = loadedSeMap_.find(key);

	//音源がない場合
	if (it == loadedSeMap_.end())
	{
		// stringキーを取得
		const std::string stringKey = SoundType::GetStringFromSE(key);

		// サウンドを取得して読み込み処理
		auto sound = resourceManager_.GetResourceSound(stringKey);
		resourceManager_.GetHandle(stringKey);

		// サウンドの管理マップに登録
		Add(stringKey, sound);
	}

	// 音量調整
	loadedSeMap_[key].volume = defaultVolumeSe_;
	ChangeVolumeSe(defaultVolumeSe_, key);

	//再生
	PlaySoundMem(loadedSeMap_[key].handle, loadedSeMap_[key].playType, topPos);
}

void SoundManager::StopBgm(const SoundType::BGM key)
{
	//音源があるか確認
	auto it = loadedBgmMap_.find(key);

	//音源がない場合終了
	if (it == loadedBgmMap_.end())
	{
		return;
	}

	//停止
	StopSoundMem(loadedBgmMap_[key].handle);

	// リストから削除
	auto listIt = std::find(playingBgmList_.begin(), playingBgmList_.end(), key);
}

void SoundManager::StopSe(const SoundType::SE key)
{
	//音源があるか確認
	auto it = loadedSeMap_.find(key);

	//音源がない場合終了
	if (it == loadedSeMap_.end())
	{
		return;
	}

	//停止
	StopSoundMem(loadedSeMap_[key].handle);
}

void SoundManager::FadeInSe(const SoundType::SE key, const int speed)
{
	//音源があるか確認
	auto it = loadedSeMap_.find(key);

	//音源がない場合終了
	if (it == loadedSeMap_.end())
	{
		return;
	}

	// フェード情報をコピー
	FadeData data = {};
	data.soundData = loadedSeMap_[key];

	// フェードイン設定
	data.fadeType = FADE::FADE_IN;

	//フェード管理に格納
	fadeSeMap_.emplace(key, data);
}

void SoundManager::FadeOutSe(const SoundType::SE key, const int speed)
{
	//音源があるか確認
	auto it = loadedSeMap_.find(key);

	//音源がない場合強制停止
	assert(it != loadedSeMap_.end() && "追加していない音源をフェードしようとしています");

	// 再生中か確認
	if (!CheckSoundMem(loadedSeMap_[key].handle))
	{
		return;
	}

	// フェード情報をコピー
	FadeData data = {};
	data.soundData = loadedSeMap_[key];

	// フェードアウト設定
	data.fadeType = FADE::FADE_OUT;

	//フェード管理に格納
	fadeSeMap_.emplace(key, data);
}

void SoundManager::StopAllSe()
{
	for (auto& se : loadedSeMap_)
	{
		if (CheckSoundMem(se.second.handle))
		{
			StopSoundMem(se.second.handle);
		}
	}
}

void SoundManager::ChangeVolumeBgm(const int volume, const SoundType::BGM bgm)
{
	// 音量の範囲チェック
	int inputVolume = volume;
	if (inputVolume < 0)
	{
		inputVolume = 0;
	}
	if (inputVolume > MAX)
	{
		inputVolume = MAX;
	}

	// マスター音量を考慮した音量計算
	int calculatedVolume = 0;
	if (defaultVolumeBgm_ > 0)
	{
		calculatedVolume = static_cast<int>(static_cast<float>(MAX * defaultVolumeBgm_) / 100.0f);
	}

	// 音源の存在確認と音量変更
	auto it = loadedBgmMap_.find(bgm);
	if (it != loadedBgmMap_.end())
	{
		ChangeVolumeSoundMem(calculatedVolume, it->second.handle);
	}
}

void SoundManager::ChangeVolumeSe(const int volume, const SoundType::SE se)
{
	// 音量の範囲チェック
	int inputVolume = volume;
	if (inputVolume < 0)
	{
		inputVolume = 0;
	}
	if (inputVolume > MAX)
	{
		inputVolume = MAX;
	}

	// マスター音量を考慮した音量計算
	int calculatedVolume = 0;
	if (defaultVolumeSe_ > 0)
	{

		calculatedVolume = static_cast<int>(static_cast<float>(MAX * defaultVolumeSe_) / 100.0f);
	}

	// 音源の存在確認と音量変更
	auto it = loadedSeMap_.find(se);
	if (it != loadedSeMap_.end())
	{
		ChangeVolumeSoundMem(calculatedVolume, it->second.handle);
	}
} 

bool SoundManager::IsCheckPlaySe(const SoundType::SE se) const
{
	//音源があるか確認
	auto it = loadedSeMap_.find(se);

	//音源がない場合強制停止
	assert(it != loadedSeMap_.end() && "追加していない音源の確認をしようとしています");

	// 再生中か確認
	return CheckSoundMem(loadedSeMap_.at(se).handle);
}

void SoundManager::Release()
{
	loadedBgmMap_.clear();
	loadedSeMap_.clear();
	fadeSeMap_.clear();
}

void SoundManager::SetDefaultVolumeBgm(const int volume)
{
	defaultVolumeBgm_ = volume;

	for(auto & bgm : playingBgmList_)
	{
		ChangeVolumeBgm(defaultVolumeBgm_, bgm);
	}
}

int SoundManager::GetPlayType(const TYPE soundType)
{
	switch (soundType)
	{
	case TYPE::SE:
		return DX_PLAYTYPE_BACK;
		break;

	case TYPE::BGM:
		return DX_PLAYTYPE_LOOP;
		break;

	default:
		break;
	}
	return -1;
}

void SoundManager::Add(const std::string& key, ResourceSound* resource)
{	
	// 音源の種類を取得
	TYPE type = resource->GetSoundType();

	// サウンドデータの格納
	SoundData soundData = {};
	soundData.playType = GetPlayType(type);		// 再生方法
	soundData.handle = resource->GetHandle();	// ハンドル
	soundData.volume = 0;						// 音量

	// 音源の種類別に格納
	if (type == TYPE::BGM)
	{
		// キーから列挙型値に変換
		const BGM bgmKey = SoundType::KEY_BGM_MAP.at(key);

		// 格納
		loadedBgmMap_.emplace(bgmKey, soundData);
	}
	else if (type == TYPE::SE)
	{
		// キーから列挙型値に変換
		const SE seKey = SoundType::KEY_SE_MAP.at(key);

		// 格納
		loadedSeMap_.emplace(seKey, soundData);
	}
}

SoundManager::SoundManager() :
	resourceManager_(ResourceManager::GetInstance())
{
	defaultVolumeBgm_ = DEFAULT_BGM_VOLUME;
	defaultVolumeSe_ = DEFAULT_SE_VOLUME;
	fadeSeMap_.clear();
}
