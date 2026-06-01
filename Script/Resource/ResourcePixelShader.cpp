#include <Dxlib.h>
#include "ResourcePixelShader.h"

ResourcePixelShader::ResourcePixelShader(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds):
	ResourceBase(type, path, sceneIds)
{
}

ResourcePixelShader::~ResourcePixelShader()
{
}

void ResourcePixelShader::Load()
{
	handleId_ = LoadPixelShader(path_.c_str());
}

void ResourcePixelShader::Release()
{
	DeleteShader(handleId_);
}
