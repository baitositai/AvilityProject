#include <DxLib.h>
#include "ResourceSprite.h"

ResourceSprite::ResourceSprite(const RESOURCE_TYPE type, const std::wstring& path, const std::vector<int>& sceneIds, const int divX, const int divY, const int sizeX, const int sizeY):
	ResourceBase(type, path, sceneIds),
	divX_(divX),
	divY_(divY),
	sizeX_(sizeX),
	sizeY_(sizeY)
{
	handleIds_ = nullptr;
}

ResourceSprite::~ResourceSprite()
{
}

void ResourceSprite::Load()
{
	// ï™äÑêîÇ…âûÇ∂ÇƒÉÅÉÇÉäämï€
	handleIds_ = new int[divX_ * divY_];

	LoadDivGraph(
		path_.c_str(),
		divX_ * divY_,
		divX_,
		divY_,
		sizeX_,
		sizeY_,
		&handleIds_[0]);
}

void ResourceSprite::Release()
{
	int num = divX_ * divY_;
	for (int i = 0; i < num; i++)
	{
		DeleteGraph(handleIds_[i]);
	}
	delete[] handleIds_;
}

const Vector2 ResourceSprite::GetDivsion() const
{
	return Vector2(divX_, divY_);
}

const Vector2 ResourceSprite::GetSize() const
{
	return Vector2(sizeX_, sizeY_);
}
