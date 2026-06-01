#include <DxLib.h>
#include "ResourceAnimation.h"

ResourceAnimation::ResourceAnimation(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds) :
	ResourceBase(type, path, sceneIds)
{
}

ResourceAnimation::~ResourceAnimation()
{
}

void ResourceAnimation::Load()
{
	handleId_ = MV1LoadModel(path_.c_str());
}

void ResourceAnimation::Release()
{
	MV1DeleteModel(handleId_);
}