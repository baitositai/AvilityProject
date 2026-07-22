#include "../common/Pixel/PixelShader2DHeader.hlsli"
#include "../common/Pixel/PixelShaderCommonFunction.hlsli"

// 定数バッファ
cbuffer ConstantBuffer : register(b4)
{
    float3 g_color; // 乗算色
    float g_alpha; // 透過値
    float2 g_division; // 分割数
    float g_draw_index; // 描画番号
    float dummy;
    float3 g_damage_color; // ダメージカラー
    float g_outLineRate;
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 1. スプライトアニメーション適用後のUV取得
    float2 uv = ApplySpriteAnimation(PSInput.uv, g_division, g_draw_index);
    
    // Feature Level 9_3 対策：画面上のUVの変化量を明示的に計算
    float2 dx = ddx(uv);
    float2 dy = ddy(uv);

    // 2. 元のキャラのテクスチャサンプリング (SampleGrad を使用)
    float4 mainColor = tex.SampleGrad(texSampler, uv, dx, dy);
    
    // 3. キャラ本来のアウトライン処理
    float2 texelSize = (1.0f / g_division) * (0.005f * g_outLineRate);
    
    // 4. 上下左右（4方向）の透明度をチェック (SampleGrad を使用)
    float alphaTop = tex.SampleGrad(texSampler, uv + float2(0.0f, -texelSize.y), dx, dy).a;
    float alphaBottom = tex.SampleGrad(texSampler, uv + float2(0.0f, texelSize.y), dx, dy).a;
    float alphaLeft = tex.SampleGrad(texSampler, uv + float2(-texelSize.x, 0.0f), dx, dy).a;
    float alphaRight = tex.SampleGrad(texSampler, uv + float2(texelSize.x, 0.0f), dx, dy).a;
    
    float maxNeighborAlpha = max(max(alphaTop, alphaBottom), max(alphaLeft, alphaRight));
    float outlineFactor = saturate(maxNeighborAlpha - mainColor.a);
    
    // 5. キャラ本体とアウトライン色の合成（赤色固定アウトライン）
    float3 outlineColor = float3(0.75f, 0.3f, 0.9f);
    float3 charRGB = lerp(mainColor.rgb, outlineColor, outlineFactor);
    
    // 6. ダメージカラーの合成
    float damageIntensity = max(g_damage_color.x, max(g_damage_color.y, g_damage_color.z));
    charRGB = lerp(charRGB, g_damage_color, damageIntensity);
    
    // 7. 全体の乗算色適用
    charRGB *= g_color;
    
    // 8. アルファ値（透明度）の計算
    float charAlpha = mainColor.a * g_alpha;
    float finalAlpha = max(charAlpha, maxNeighborAlpha * g_alpha);
    
    // 9. ピクセル破棄（完全に透明な場合は非表示）
    if (finalAlpha <= 0.0f)
        discard;
    
    // 出力
    return float4(charRGB, finalAlpha);
}