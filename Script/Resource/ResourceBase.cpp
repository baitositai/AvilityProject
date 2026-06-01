#include "ResourceBase.h"

ResourceBase::ResourceBase(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds) :
	type_(type),
	path_(path),
	sceneIds_(sceneIds)
{
	handleId_ = -1;
}
