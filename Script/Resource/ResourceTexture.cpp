#include <DxLib.h>
#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds, const int divX, const int divY, const int sizeX, const int sizeY) :
	ResourceBase(type, path, sceneIds),
	divX_(divX),
	divY_(divY),
	sizeX_(sizeX),
	sizeY_(sizeY)
{
}

ResourceTexture::~ResourceTexture()
{
}

void ResourceTexture::Load()
{
	handleId_ = LoadGraph(path_.c_str());
}

void ResourceTexture::Release()
{
	DeleteGraph(handleId_);
}

const Vector2 ResourceTexture::GetDivsion() const
{
	return Vector2(divX_, divY_);
}

const Vector2 ResourceTexture::GetSize() const
{
	return Vector2(sizeX_, sizeY_);
}