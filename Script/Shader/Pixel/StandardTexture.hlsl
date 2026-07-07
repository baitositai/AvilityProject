#include "../common/Pixel/PixelShader2DHeader.hlsli"

// 定数バッファ
cbuffer ConstantBuffer : register(b4)
{
    float3 g_color;         // 乗算色
    float g_alpha;          // 透過値
    float g_is_reverse_x;   // X軸反転(1.0で反転)
    float g_is_reverse_y;   // Y軸反転(1.0で反転)
    float g_angle;          // 角度(ラジアン値)
    float dummy;
    float2 g_graph_size;    // 画像サイズ
    float2 dummy2;     
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 中心を基準にするため一時的に中心をずらす
    float2 uv = PSInput.uv - 0.5f;
    
    // テクスチャ自体の縦横比を計算
    float aspect = g_graph_size.x / g_graph_size.y;
    
    // 回転させる前に、横幅をアスペクト比で補正してUV空間を疑似的に正方形にする
    uv.x *= aspect;
    
    // 回転
    float sinAngle = sin(g_angle);
    float cosAngle = cos(g_angle);
    float2 rotatedUv;
    rotatedUv.x = uv.x * cosAngle + uv.y * sinAngle;
    rotatedUv.y = -uv.x * sinAngle + uv.y * cosAngle;
    uv = rotatedUv;
    
    // 回転が終わったら、補正していたアスペクト比を元に戻す
    uv.x /= aspect;
    
    // 反転
    float2 reverseSign = float2(1.0f - 2.0f * g_is_reverse_x, 1.0f - 2.0f * g_is_reverse_y);
    uv *= reverseSign;
    
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