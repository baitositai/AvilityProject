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
float2 uv = PSInput.uv;

    // 反転処理を回転の前に行う
    float2 reverseSign = float2(1.0f - 2.0f * g_is_reverse_x, 1.0f - 2.0f * g_is_reverse_y);
    uv = (uv - 0.5f) * reverseSign + 0.5f;

    // 中心を基準にするため一時的に中心をずらす
    uv -= 0.5f;

    // テクスチャのアスペクト比を計算
    float aspect = g_graph_size.x / g_graph_size.y;

    // 回転前のUVを、実際の画像の縦横比（物理空間）に合わせる
    // Y軸を基準とし、X軸をアスペクト比倍することで、UV空間を擬似的に正しい比率の長方形にする
    uv.x *= aspect;

    // 回転行列の適用
    float sinAngle = sin(g_angle);
    float cosAngle = cos(g_angle);
    
    float2 rotatedUv;
    // 物理空間（正しい比率）のまま回転させるため、歪みが発生しない
    rotatedUv.x = uv.x * cosAngle + uv.y * sinAngle;
    rotatedUv.y = -uv.x * sinAngle + uv.y * cosAngle;
    uv = rotatedUv;

    // 回転が終わったら、描画先ポリゴンのUV空間（0.0 ~ 1.0）に適合させるため、アスペクト比の補正を解除する
    uv.x /= aspect;

    // 中心を戻す
    uv += 0.5f;

    // テクスチャサンプリング
    float4 mainColor = tex.Sample(texSampler, uv);

    mainColor.rgb *= g_color;
    mainColor.a *= g_alpha;

    return mainColor;
}