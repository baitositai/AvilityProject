#pragma once
#include <string>
#include <unordered_map>

class ResourceBase
{
public:

	/// <summary>
	/// リソースタイプ
	/// </summary>
	enum class RESOURCE_TYPE
	{
		MODEL,
		TEXTUR,
		SPRITE,
		EFFECT,
		SOUND,
		FONT,
		PIXEL_SHADER,
		VERTEX_SHADER,
		NONE
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="path">パス名</param>
	/// <param name="sceneIds">シーンID</param>
	ResourceBase(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ResourceBase() {};

	/// <summary>
	/// 読み込み処理
	/// </summary>
	virtual void Load() {};

	/// <summary>
	/// 解放処理
	/// </summary>
	virtual void Release() {};

	/// <summary>
	/// 種類を返す
	/// </summary>
	/// <returns>種類</returns>
	const RESOURCE_TYPE GetType() const { return type_; }

	/// <summary>
	/// ハンドルを返す
	/// </summary>
	/// <returns>ハンドル</returns>
	virtual const int GetHandle() { return handleId_; }

	/// <summary>
	/// シーンIDを返す
	/// </summary>
	/// <returns></returns>
	const std::vector<int> GetSceneIds() const { return sceneIds_; }

protected:

	//種類
	RESOURCE_TYPE type_;

	//パス
	std::wstring path_;

	//シーンID
	std::vector<int> sceneIds_;

	//ハンドル
	int handleId_;

};