#include "../common/Pixel/PixelShader2DHeader.hlsli"
#include "../common/Pixel/PixelShaderCommonFunction.hlsli"

// 定数バッファ
cbuffer ConstantBuffer : register(b4)
{
    float3 g_color;         // 乗算色
    float g_alpha;          // 透過値
    float2 g_division;      // 分割数
    float g_draw_index;     // 描画番号
    float dummy;
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    float2 uv = PSInput.uv;
    
    // 共通関数を使ってスプライトのアニメーション位置を適用する
    uv = ApplySpriteAnimation(uv, g_division, g_draw_index);
    
    // テクスチャサンプリング
    float4 mainColor = tex.Sample(texSampler, uv);
    
    // カラーの乗算
    mainColor.rgb *= g_color;
    
    // 透過処理
    mainColor.a *= g_alpha;
    
    // 出力
    return mainColor;
}