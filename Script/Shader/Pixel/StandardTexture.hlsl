#include "../common/Pixel/PixelShader2DHeader.hlsli"

// 定数バッファ
cbuffer ConstantBuffer : register(b4)
{
    float3 g_color;         // 乗算色
    float g_alpha;          // 透過値
    float g_is_reverse_x;   // X軸反転(1.0で反転)
    float g_is_reverse_y;   // Y軸反転(1.0で反転)
    float g_scale;          // 拡大率
    float g_angle;          // 角度(ラジアン値)
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 基準用の中心UV値
    float2 uv = PSInput.uv - 0.5f;
    
    // 反転処理
    float2 reverseSign = float2(1.0f - 2.0f * g_is_reverse_x, 1.0f - 2.0f * g_is_reverse_y);
    uv *= reverseSign;
    
    // 回転
    float sinAngle = sin(g_angle);
    float cosAngle = cos(g_angle);
    float2 rotatedUv;
    rotatedUv.x = uv.x * cosAngle - uv.y * sinAngle;
    rotatedUv.y = uv.x * sinAngle + uv.y * cosAngle;
    uv = rotatedUv;
    
    // 中心を戻す
    uv += 0.5f;
    
    // テクスチャサンプリング
    float4 mainColor = tex.Sample(texSampler, uv);
    
    // カラーの乗算
    mainColor.rgb *= g_color;
    
    // 透過処理
    mainColor.a *= g_alpha;
    
    return mainColor;
}