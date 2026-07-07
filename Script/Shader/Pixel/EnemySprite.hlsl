#include "../common/Pixel/PixelShader2DHeader.hlsli"
#include "../common/Pixel/PixelShaderCommonFunction.hlsli"

// 定数バッファ
cbuffer ConstantBuffer : register(b4)
{
    float3 g_color;             // 乗算色
    float g_alpha;              // 透過値
    float g_is_reverse_x;       // X軸反転(1.0で反転)
    float g_is_reverse_y;       // Y軸反転(1.0で反転)
    float g_angle;              // 角度(ラジアン値)
    float g_draw_index;         // 描画番号
    float2 g_division;          // 分割数
    float2 g_graph_size;        // 画像サイズ
    float3 g_damage_color;      // ダメージカラー
    float dummy;
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 回転・反転・アスペクト比補正を行う
    float2 uv = CalculateSpriteUv(PSInput.uv, g_graph_size, g_division, g_angle, g_is_reverse_x, g_is_reverse_y);
    
    // 共通関数を使ってスプライトのアニメーション位置を適用する
    uv = ApplySpriteAnimation(uv, g_division, g_draw_index);
    
    // テクスチャサンプリング
    float4 mainColor = tex.Sample(texSampler, uv);
    
    // ダメージ時に線形補間を使って特定の色で塗りつぶす
    float damageIntensity = max(g_damage_color.x, max(g_damage_color.y, g_damage_color.z));
    mainColor.rgb = lerp(mainColor.rgb, g_damage_color, damageIntensity);
    
    // カラーの乗算
    mainColor.rgb *= g_color;
    
    // 透過処理
    mainColor.a *= g_alpha;
    
    // 出力
    return mainColor;
}