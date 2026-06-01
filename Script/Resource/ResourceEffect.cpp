#include <EffekseerForDXLib.h>
#include <Effekseer.h>
#include "ResourceEffect.h"

ResourceEffect::ResourceEffect(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds)	:
	ResourceBase(type, path, sceneIds)
{
}

ResourceEffect::~ResourceEffect()
{
}

void ResourceEffect::Load()
{
	handleId_ = LoadEffekseerEffect(path_.c_str());
}

void ResourceEffect::Release()
{
	DeleteEffekseerEffect(handleId_);
}
