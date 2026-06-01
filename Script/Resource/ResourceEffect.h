#pragma once
#include "ResourceBase.h"

class ResourceEffect : public ResourceBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="path">パス名</param>
	/// <param name="sceneIds">シーンID</param>
	ResourceEffect(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResourceEffect()override;

	/// <summary>
	/// 読み込み処理
	/// </summary>
	void Load()override;

	/// <summary>
	/// 解放処理
	/// </summary>
	void Release()override;

};

