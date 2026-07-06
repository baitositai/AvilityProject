#pragma once
#include <unordered_map>
#include <string>
#include "../../Template/Singleton.h"
#include "../../Resource/ResourceBase.h"
#include "../../Common/Vector2.h"

class ResourceBase;
class ResourceSound;
class ResourceSprite;
class ResourceTexture;
class ResourceEffect;

class ResourceManager : public Singleton<ResourceManager>
{

	friend class Singleton<ResourceManager>;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// リソースの完全解放
	/// </summary>
	void Release();

	/// <summary>
	/// リソース単体での解放
	/// </summary>
	/// <param name="key">リソースキー</param>
	void SoloRelease(const std::string& key);

	/// <summary>
	/// シーン変更の処理
	/// </summary>
	/// <param name="nextSceneId">次シーンのID</param>
	void SceneChangeResource(const int nextSceneId);

	/// <summary>
	/// シーンで用いるサウンドを返す
	/// </summary>
	/// <returns>シーンで用いるサウンド</returns>
	std::unordered_map<std::string, ResourceSound*>& GetSceneSounds() const;

	/// <summary>
	/// シーンで用いるエフェクトを返す
	/// </summary>
	/// <returns>シーンで用いるエフェクト</returns>
	std::unordered_map<std::string, ResourceEffect*>& GetSceneEffects() const;

	/// <summary>
	/// 指定したキーのリソースを返す
	/// </summary>
	/// <param name="key">リソースキー</param>
	/// <returns>リソースのハンドル</returns>
	int GetHandle(const std::string& key);

	/// <summary>
	/// 指定したキーのリソースを返す
	/// </summary>
	/// <param name="key">リソースキー</param>
	/// <returns>リソースのハンドル(主にスプライト)</returns>
	int* GetHandles(const std::string& key);

	/// <summary>
	/// 指定したキーのスプライトを返す
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	ResourceSprite* GetResourceSprite(const std::string& key);

	/// <summary>
	/// 指定したキーのサウンドを返す
	/// </summary>
	/// <param name="key">リリースキー</param>
	/// <returns>サウンドを返す</returns>
	ResourceTexture* GetResourceTexture(const std::string& key);

	/// <summary>
	/// 指定したキーのサウンドを返す
	/// </summary>
	/// <param name="key">リリースキー</param>
	/// <returns>サウンドを返す</returns>
	ResourceSound* GetResourceSound(const std::string& key);

	/// <summary>
	/// 指定したキーのフォントの名前を返す
	/// </summary>
	/// <param name="key">リソースキー</param>
	/// <returns>フォントの名前</returns>
	const std::wstring GetFontName(const std::string& key);

private:

	// リソース管理の対象
	std::unordered_map<std::string, std::unique_ptr<ResourceBase>> resourcesMap_;

	// 読み込み済みリソース
	std::unordered_map<std::string, ResourceBase*> loadedMap_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager();
	~ResourceManager() = default;
};