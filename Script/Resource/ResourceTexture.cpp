#include <DxLib.h>
#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds):
	ResourceBase(type, path, sceneIds)
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
