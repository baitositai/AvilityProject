#include <DxLib.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../../Application.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Resource/ResourceBase.h"
#include "../../Resource/ResourceEffect.h"
#include "../../Resource/ResourceFont.h"
#include "../../Resource/ResourceModel.h"
#include "../../Resource/ResourcePixelShader.h"
#include "../../Resource/ResourceSound.h"
#include "../../Resource/ResourceSprite.h"
#include "../../Resource/ResourceTexture.h"
#include "../../Resource/ResourceVertexShader.h"
#include "ResourceManager.h"

// JSON名前空間
using json = nlohmann::json;

// 文字列からenum の対応表
static const std::unordered_map<std::string, ResourceBase::RESOURCE_TYPE> RESOURCE_TYPE_MAP =
{
	{"model", ResourceBase::RESOURCE_TYPE::MODEL},
	{"sprite", ResourceBase::RESOURCE_TYPE::SPRITE},
	{"texture", ResourceBase::RESOURCE_TYPE::TEXTUR},
	{"sound", ResourceBase::RESOURCE_TYPE::SOUND},
	{"font", ResourceBase::RESOURCE_TYPE::FONT},
	{"effect", ResourceBase::RESOURCE_TYPE::EFFECT},
	{"pixelShader", ResourceBase::RESOURCE_TYPE::PIXEL_SHADER},
	{"vertexShader", ResourceBase::RESOURCE_TYPE::VERTEX_SHADER}
};

void ResourceManager::Init()
{
	int divX = -1;
	int divY = -1;
	int sizeX = -1;
	int sizeY = -1;
	std::vector<int> sceneIds = {};
	std::string key = "";
	std::string soundType = "";
	std::string stringType = "";
	std::wstring path = L"";
	std::string fontName = "";

	std::ifstream ifs((Application::PATH_JSON + "Resources.json").c_str());

	assert(ifs.is_open() && "ファイルが開けません");

	json j;
	ifs >> j;

	for (auto& res : j["resources"])
	{
		key = res["key"].get<std::string>();
		stringType = res["type"].get<std::string>();
		path = UtilityCommon::GetWStringFromString(res["path"].get<std::string>());
		sceneIds = res["sceneIds"].get<std::vector<int>>();

		auto it = RESOURCE_TYPE_MAP.find(stringType);
		assert(it != RESOURCE_TYPE_MAP.end() && "登録されてない種類です");
		ResourceBase::RESOURCE_TYPE type = it->second;

		std::unique_ptr<ResourceBase> resource;
		switch (type)
		{
		case ResourceBase::RESOURCE_TYPE::MODEL:
			resource = make_unique<ResourceModel>(type, path, sceneIds);
			break;

		case ResourceBase::RESOURCE_TYPE::TEXTUR:
			divX = res["divX"].get<int>();
			divY = res["divY"].get<int>();
			sizeX = res["sizeX"].get<int>();
			sizeY = res["sizeY"].get<int>();
			resource = make_unique<ResourceTexture>(type, path, sceneIds, divX, divY, sizeX, sizeY);
			break;

		case ResourceBase::RESOURCE_TYPE::SPRITE:
			divX = res["divX"].get<int>();
			divY = res["divY"].get<int>();
			sizeX = res["sizeX"].get<int>();
			sizeY = res["sizeY"].get<int>();
			resource = make_unique<ResourceSprite>(type, path, sceneIds, divX, divY, sizeX, sizeY);
			break;

		case ResourceBase::RESOURCE_TYPE::EFFECT:
			resource = make_unique<ResourceEffect>(type, path, sceneIds);
			break;

		case ResourceBase::RESOURCE_TYPE::SOUND:
			soundType = res["soundType"].get<std::string>();
			resource = make_unique<ResourceSound>(type, path, soundType, sceneIds);
			break;

		case ResourceBase::RESOURCE_TYPE::FONT:
			fontName = UtilityCommon::ConvertUtf8ToSjis((res["fontName"].get<std::string>().c_str()));
			resource = make_unique<ResourceFont>(type, path, sceneIds, UtilityCommon::GetWStringFromString(fontName));
			break;

		case ResourceBase::RESOURCE_TYPE::PIXEL_SHADER:
			resource = make_unique<ResourcePixelShader>(type, path, sceneIds);
			break;

		case ResourceBase::RESOURCE_TYPE::VERTEX_SHADER:
			resource = make_unique<ResourceVertexShader>(type, path, sceneIds);
			break;

		default:
			break;
		}

		resourcesMap_.emplace(key, std::move(resource));
	}

	for (auto& p : resourcesMap_)
	{
		const auto& ids = p.second->GetSceneIds();

		if (std::ranges::find(ids, 0) != ids.end())
		{
			p.second->Load();

			loadedMap_.emplace(p.first, p.second.get());
		}
	}
}

void ResourceManager::Release()
{
	for (auto& p : loadedMap_)
	{
		p.second->Release();
	}

	loadedMap_.clear();
	resourcesMap_.clear();
}

void ResourceManager::SoloRelease(const std::string& key)
{
	// リソースを探す
	auto it = loadedMap_.find(key);

	// 見つからなかった場合
	if (it == loadedMap_.end())
	{
		// 無視
		return;
	}

	// 解放処理を行う
	it->second->Release();

	// マップから要素を削除する
	loadedMap_.erase(it);
}

void ResourceManager::SceneChangeResource(const int nextSceneId)
{
	for (auto it = loadedMap_.begin(); it != loadedMap_.end(); )
	{
		const auto& ids = it->second->GetSceneIds();

		// シーンIDが空、または0が含まれていない場合は解放する
		if (ids.empty() || std::ranges::find(ids, 0) == ids.end())
		{
			it->second->Release();
			it = loadedMap_.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto& p : resourcesMap_)
	{
		const auto& ids = p.second->GetSceneIds();

		if (std::ranges::find(ids, nextSceneId) != ids.end())
		{
			p.second->Load();
			loadedMap_.emplace(p.first, p.second.get());
		}
	}
}

std::unordered_map<std::string, ResourceSound*>& ResourceManager::GetSceneSounds() const
{
	// シーンリソースを格納するマップ
	static std::unordered_map<std::string, ResourceSound*> sceneSounds;

	// 空じゃないか確認
	if (loadedMap_.empty())
	{
		return sceneSounds;
	}

	// 指定した種類のリソースを探す
	for (auto& p : resourcesMap_)
	{
		// 指定した種類のリソースだけを抽出
		if (p.second->GetType() == ResourceBase::RESOURCE_TYPE::SOUND)
		{
			// 読み込んだリソースか確認
			auto it = loadedMap_.find(p.first);
			if (it != loadedMap_.end())
			{
				// 実行時型チェック
				ResourceSound* sound = dynamic_cast<ResourceSound*>(p.second.get());
				
				// 型が正しい場合
				if (sound != nullptr)
				{
					// 格納	
					sceneSounds.emplace(p.first, sound);
				}
				// 型が不正な場合
				else 
				{
					assert(false && "型情報がSOUNDなのにキャストに失敗しました");
				}
			}
		}
	}

	// シーンリソースを返す
	return sceneSounds;
}

std::unordered_map<std::string, ResourceEffect*>& ResourceManager::GetSceneEffects() const
{
	// シーンリソースを格納するマップ
	static std::unordered_map<std::string, ResourceEffect*> sceneEffects;

	// 空じゃないか確認
	if (loadedMap_.empty())
	{
		assert(false && "読み込んだリソースがありません");
		return sceneEffects;
	}

	// 指定した種類のリソースを探す
	for (auto& p : resourcesMap_)
	{
		// 指定した種類のリソースだけを抽出
		if (p.second->GetType() == ResourceBase::RESOURCE_TYPE::EFFECT)
		{
			// 読み込んだリソースか確認
			auto it = loadedMap_.find(p.first);
			if (it != loadedMap_.end())
			{
				// 実行時型チェック
				ResourceEffect* sound = dynamic_cast<ResourceEffect*>(p.second.get());

				// 型が正しい場合
				if (sound != nullptr)
				{
					// 格納	
					sceneEffects.emplace(p.first, sound);
				}
				// 型が不正な場合
				else
				{
					assert(false && "型情報がEFFECTなのにキャストに失敗しました");
				}
			}
		}
	}

	// シーンリソースを返す
	return sceneEffects;
}

int ResourceManager::GetHandle(const std::string& key) 
{
	// 読み込み済みマップから探す
	auto it = loadedMap_.find(key);

	// 見つかった場合
	if (it != loadedMap_.end())
	{
		// そのまま返す
		return it->second->GetHandle();
	}

	// リソースマップから探す
	auto res = resourcesMap_.find(key);

	// 見つからない場合
	if (res == resourcesMap_.end())
	{
		// 終了
		return -1;
	}

	// リソースを取得して読み込み処理
	ResourceBase* resPtr = res->second.get();
	resPtr->Load();

	// 読み込み済みマップに登録する
	loadedMap_.emplace(key, resPtr);

	// ハンドルを返す
	return resPtr->GetHandle();
}

int* ResourceManager::GetHandles(const std::string& key) 
{
	// 読み込み済みマップから探す
	auto it = loadedMap_.find(key);

	// 見つかった場合
	if (it != loadedMap_.end())
	{
		// 派生型にキャスト
		auto sprite = dynamic_cast<ResourceSprite*>(it->second);

		// そのまま返す
		return sprite->GetHandleIds();
	}

	// リソースマップから探す
	auto res = resourcesMap_.find(key);

	// 見つからない場合
	if (res == resourcesMap_.end())
	{
		// 終了
		return nullptr;
	}

	// リソースを取得して読み込み処理
	ResourceBase* resPtr = res->second.get();
	resPtr->Load();

	// 読み込み済みマップに登録する
	loadedMap_.emplace(key, resPtr);

	// 派生型にキャスト
	auto sprite = dynamic_cast<ResourceSprite*>(it->second);

	// そのまま返す
	return sprite->GetHandleIds();
}

ResourceSprite* ResourceManager::GetResourceSprite(const std::string& key)
{
	// 読み込み済みマップから探す
	auto itLoaded = loadedMap_.find(key);

	// 見つかった場合
	if (itLoaded != loadedMap_.end())
	{
		// キャストして返す
		return dynamic_cast<ResourceSprite*>(itLoaded->second);
	}

	// リソースマップから探す
	auto itResource = resourcesMap_.find(key);

	// 見つからない場合
	if (itResource == resourcesMap_.end())
	{
		// 終了
		return nullptr;
	}

	// リソースを取得して読み込み処理
	ResourceBase* pRawResource = itResource->second.get();
	pRawResource->Load();

	// 読み込み済みマップに登録する
	loadedMap_.emplace(key, pRawResource);

	// 取得したリソースをキャストして返す
	return dynamic_cast<ResourceSprite*>(pRawResource);
}

ResourceTexture* ResourceManager::GetResourceTexture(const std::string& key)
{
	// 読み込み済みマップから探す
	auto itLoaded = loadedMap_.find(key);

	// 見つかった場合
	if (itLoaded != loadedMap_.end())
	{
		// キャストして返す
		return dynamic_cast<ResourceTexture*>(itLoaded->second);
	}

	// リソースマップから探す
	auto itResource = resourcesMap_.find(key);

	// 見つからない場合
	if (itResource == resourcesMap_.end())
	{
		// 終了
		return nullptr;
	}

	// リソースを取得して読み込み処理
	ResourceBase* pRawResource = itResource->second.get();
	pRawResource->Load();

	// 読み込み済みマップに登録する
	loadedMap_.emplace(key, pRawResource);

	// 取得したリソースをキャストして返す
	return dynamic_cast<ResourceTexture*>(pRawResource);
}

ResourceSound* ResourceManager::GetResourceSound(const std::string& key)
{
	// 読み込み済みマップから探す
	auto itLoaded = loadedMap_.find(key);

	// 見つかった場合
	if (itLoaded != loadedMap_.end())
	{
		// キャストして返す
		return dynamic_cast<ResourceSound*>(itLoaded->second);
	}

	// リソースマップから探す
	auto itResource = resourcesMap_.find(key);

	// 見つからない場合
	if (itResource == resourcesMap_.end())
	{
		// 終了
		return nullptr;
	}

	// リソースを取得して読み込み処理
	ResourceBase* pRawResource = itResource->second.get();
	pRawResource->Load();

	// 読み込み済みマップに登録する
	loadedMap_.emplace(key, pRawResource);

	// 取得したリソースをキャストして返す
	return dynamic_cast<ResourceSound*>(pRawResource);
}

const std::wstring ResourceManager::GetFontName(const std::string& key) 
{
	// 読み込み済みマップから探す
	auto it = loadedMap_.find(key);

	// 見つかった場合
	if (it != loadedMap_.end())
	{
		// 派生型にキャスト
		auto sprite = dynamic_cast<ResourceFont*>(it->second);

		// そのまま返す
		return sprite->GetFontName();
	}

	// リソースマップから探す
	auto res = resourcesMap_.find(key);

	// 見つからない場合
	if (res == resourcesMap_.end())
	{
		// 終了
		return L"";
	}

	// リソースを取得して読み込み処理
	ResourceBase* resPtr = res->second.get();
	resPtr->Load();

	// 読み込み済みマップに登録する
	loadedMap_.emplace(key, resPtr);

	// 派生型にキャスト
	auto sprite = dynamic_cast<ResourceFont*>(it->second);

	// そのまま返す
	return sprite->GetFontName();
}

ResourceManager::ResourceManager(void)
{

}