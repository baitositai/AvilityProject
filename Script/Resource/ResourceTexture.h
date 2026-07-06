#pragma once
#include "ResourceBase.h"
#include "../Common/Vector2.h"

class ResourceTexture : public ResourceBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="path">パス名</param>
	/// <param name="sceneIds">シーンID</param>
	/// <param name="divX">分割数X</param>
	/// <param name="divY">分割数Y</param>
	/// <param name="sizeX">サイズX</param>
	/// <param name="sizeY">サイズY</param>
	ResourceTexture(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds, const int divX, const int divY, const int sizeX, const int sizeY);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResourceTexture()override;

	/// <summary>
	/// 読み込み処理
	/// </summary>
	void Load()override;

	/// <summary>
	/// 解放処理
	/// </summary>
	void Release()override;

	/// <summary>
	/// 分割数を返す
	/// </summary>
	/// <returns>分割数</returns>
	const Vector2 GetDivsion() const;

	/// <summary>
	/// サイズを返す
	/// </summary>
	/// <returns>サイズ</returns>
	const Vector2 GetSize() const;

private:

	//分割
	int divX_;
	int divY_;

	//サイズ
	int sizeX_;
	int sizeY_;
};