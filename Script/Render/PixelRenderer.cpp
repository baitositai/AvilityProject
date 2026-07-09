#include <cmath>
#include "PixelRenderer.h"

PixelRenderer::PixelRenderer(PixelMaterial& pixelMaterial) : 
	pixelMaterial_(pixelMaterial),
	indexes_(),
	vertexs_()
{
}

PixelRenderer::~PixelRenderer(void)
{
}

void PixelRenderer::MakeSquereVertex(const Vector2& pos, const Vector2& size, float angle, float scale, bool flipX, bool flipY)
{
	pos_ = pos;
	size_ = size;

	float halfW = static_cast<float>(size.x) / 2.0f;
	float halfH = static_cast<float>(size.y) / 2.0f;

	// ４頂点の初期化
	for (int i = 0; i < 4; i++)
	{
		vertexs_[i].rhw = 1.0f;
		vertexs_[i].dif = GetColorU8(255, 255, 255, 255);
		vertexs_[i].spc = GetColorU8(255, 255, 255, 255);
		vertexs_[i].su = 0.0f;
		vertexs_[i].sv = 0.0f;
	}

	// 反転と拡大率を考慮したローカル座標の係数
	float flipXScale = flipX ? -1.0f : 1.0f;
	float flipYScale = flipY ? -1.0f : 1.0f;

	// 中心を原点(0, 0)とした時の各頂点の位置（反転と拡大縮小を適用）
	float localX[4] = { -halfW * flipXScale * scale,  halfW * flipXScale * scale,  halfW * flipXScale * scale, -halfW * flipXScale * scale };
	float localY[4] = { -halfH * flipYScale * scale, -halfH * flipYScale * scale,  halfH * flipYScale * scale,  halfH * flipYScale * scale };

	// 回転用のサイン・コサインを計算
	float sinAngle = std::sin(angle);
	float cosAngle = std::cos(angle);

	int cnt = 0;

	// 左上
	float rotX0 = localX[cnt] * cosAngle - localY[cnt] * sinAngle;
	float rotY0 = localX[cnt] * sinAngle + localY[cnt] * cosAngle;
	vertexs_[cnt].pos = VGet(static_cast<float>(pos.x) + rotX0, static_cast<float>(pos.y) + rotY0, 0.0f);
	vertexs_[cnt].u = 0.0f;
	vertexs_[cnt].v = 0.0f;
	cnt++;

	// 右上
	float rotX1 = localX[cnt] * cosAngle - localY[cnt] * sinAngle;
	float rotY1 = localX[cnt] * sinAngle + localY[cnt] * cosAngle;
	vertexs_[cnt].pos = VGet(static_cast<float>(pos.x) + rotX1, static_cast<float>(pos.y) + rotY1, 0.0f);
	vertexs_[cnt].u = 1.0f;
	vertexs_[cnt].v = 0.0f;
	cnt++;

	// 右下
	float rotX2 = localX[cnt] * cosAngle - localY[cnt] * sinAngle;
	float rotY2 = localX[cnt] * sinAngle + localY[cnt] * cosAngle;
	vertexs_[cnt].pos = VGet(static_cast<float>(pos.x) + rotX2, static_cast<float>(pos.y) + rotY2, 0.0f);
	vertexs_[cnt].u = 1.0f;
	vertexs_[cnt].v = 1.0f;
	cnt++;

	// 左下
	float rotX3 = localX[cnt] * cosAngle - localY[cnt] * sinAngle;
	float rotY3 = localX[cnt] * sinAngle + localY[cnt] * cosAngle;
	vertexs_[cnt].pos = VGet(static_cast<float>(pos.x) + rotX3, static_cast<float>(pos.y) + rotY3, 0.0f);
	vertexs_[cnt].u = 0.0f;
	vertexs_[cnt].v = 1.0f;

	// 頂点インデックス（変更なし）
	cnt = 0;
	indexes_[cnt++] = 0;
	indexes_[cnt++] = 1;
	indexes_[cnt++] = 3;

	indexes_[cnt++] = 1;
	indexes_[cnt++] = 2;
	indexes_[cnt++] = 3;
}

void PixelRenderer::MakeSquereVertex(void)
{
	MakeSquereVertex(pos_, size_);
}

void PixelRenderer::SetPos(Vector2 pos)
{
	pos_ = pos;
}

void PixelRenderer::SetSize(Vector2 size)
{
	size_ = size;
}

void PixelRenderer::Draw(void)
{

	// ピクセルシェーダ設定
	SetUsePixelShader(pixelMaterial_.GetShader());

	size_t size;

	// ピクセルシェーダにテクスチャを転送
	const auto& textures = pixelMaterial_.GetTextures();
	size = textures.size();
	for (int i = 0; i < size; i++)
	{
		SetUseTextureToShader(i, textures[i]);
	}

	// 定数バッファハンドル
	int constBuf = pixelMaterial_.GetConstBuf();

	FLOAT4* constBufsPtr = (FLOAT4*)GetBufferShaderConstantBuffer(constBuf);
	const auto& constBufs = pixelMaterial_.GetConstBufs();

	size = constBufs.size();
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			constBufsPtr++;
		}
		constBufsPtr->x = constBufs[i].x;
		constBufsPtr->y = constBufs[i].y;
		constBufsPtr->z = constBufs[i].z;
		constBufsPtr->w = constBufs[i].w;
	}

	// 定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(constBuf);

	// 定数バッファをピクセルシェーダー用定数バッファレジスタにセット
	SetShaderConstantBuffer(
		constBuf, DX_SHADERTYPE_PIXEL, CONSTANT_BUF_SLOT_BEGIN_PS);

	// テクスチャアドレスタイプの取得
	auto texA = pixelMaterial_.GetTextureAddress();
	int texAType = static_cast<int>(texA);

	// テクスチャアドレスタイプを変更
	SetTextureAddressModeUV(texAType, texAType);

	// カリング無効
	SetUseBackCulling(DX_CULLING_NONE);

	// 描画
	DrawPolygonIndexed2DToShader(vertexs_, NUM_VERTEX, indexes_, NUM_POLYGON);

	// カリング有効
	SetUseBackCulling(DX_CULLING_LEFT);

	// テクスチャアドレスタイプを元に戻す
	SetTextureAddressModeUV(DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP);
	
	// 後始末
	//-----------------------------------------

	// テクスチャ解除
	size = textures.size();
	for (int i = 0; i < size; i++)
	{
		SetUseTextureToShader(i, -1);
	}

	// ピクセルシェーダ解除
	SetUsePixelShader(-1);

	// オリジナルシェーダ設定(OFF)
	MV1SetUseOrigShader(false);
	//-----------------------------------------

}

void PixelRenderer::Draw(int x, int y)
{
	pos_.x = x;
	pos_.y = y;
	MakeSquereVertex();
	Draw();
}
