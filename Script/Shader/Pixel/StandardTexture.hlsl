#include "../common/Pixel/PixelShader2DHeader.hlsli"

// 定数バッファ
cbuffer ConstantBuffer : register(b4)
{
    float3 g_color; // 乗算色
    float g_alpha; // 透過値
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    float2 uv = PSInput.uv;

    // テクスチャサンプリング
    float4 mainColor = tex.Sample(texSampler, uv);
    
    // カラーの乗算
    mainColor.rgb *= g_color;
    
    // 透過処理
    mainColor.a *= g_alpha;
    
    // 出力
    return mainColor;
}