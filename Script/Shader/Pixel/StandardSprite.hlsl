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
    float2 g_division;      // 分割数
    float g_draw_index;     // 描画番号
    float dummy;
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 中心を基準にするため一時的に中心をずらす
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
    
    // 1コマあたりのUVサイズを計算
    float2 size = 1.0f / g_division;
    
    // 描画番号から二次元配列の番号を計算
    float indexX = trunc(fmod(g_draw_index, g_division.x));
    float indexY = trunc(g_draw_index / g_division.x);
    float2 spriteIndex = float2(indexX, indexY);
    
    // 変形が終わったUVを1コマのサイズに縮小して目的のコマまで位置を調整
    uv = uv * size + (spriteIndex * size);
    
    // テクスチャサンプリング
    float4 mainColor = tex.Sample(texSampler, uv);
    
    // カラーの乗算
    mainColor.rgb *= g_color;
    
    // 透過処理
    mainColor.a *= g_alpha;
    
    // 出力
    return mainColor;
}