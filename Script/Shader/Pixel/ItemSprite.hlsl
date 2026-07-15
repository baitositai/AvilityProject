#include "../common/Pixel/PixelShader2DHeader.hlsli"
#include "../common/Pixel/PixelShaderCommonFunction.hlsli"

// 定数バッファ
cbuffer ConstantBuffer : register(b4)
{
    float3 g_color; // 乗算色
    float g_alpha; // 透過値
    float2 g_division; // 分割数
    float g_draw_index; // 描画番号
    float g_time; // C++側で加算され続ける総時間
}

// 後光（バックグロー）の設定
static const float3 GLOW_COLOR = float3(0.3f, 0.9f, 1.0f); // 後光の色（シアン・水色）
static const float GLOW_INTENSITY = 4.5f; // 後光の明るさ
static const float ITEM_SCALE = 1.35f; // アイコンの縮小率（周りの余白サイズ）

// ★ ここで速さと大きさをマイルドに微調整しました
static const float PULSE_SPEED = 8.0f; // 【調整】速すぎず遅すぎない、心地よいピカピカ速度（元の 30.0 から大幅カット）
static const float PULSE_RANGE = 0.15f; // 【調整】縮みすぎ・広がりすぎを防ぐため、変化幅を抑えました（基準 1.0 ± 0.15）

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 1. 元のUV（0.0 ~ 1.0）を取得
    float2 localUV = PSInput.uv;
    
    // 2. 中心(0.5, 0.5)を基準にUVを拡大する（＝絵自体は中央に小さくなり、周りに余白ができる）
    float2 scaledUV = (localUV - 0.5f) * ITEM_SCALE + 0.5f;
    
    // 3. 縮小によってはみ出た枠外のノイズを消去するためのマスク
    float marginMask = (scaledUV.x >= 0.0f && scaledUV.x <= 1.0f && scaledUV.y >= 0.0f && scaledUV.y <= 1.0f) ? 1.0f : 0.0f;
    
    // 4. 縮小したUVに対してアニメーション位置を適用
    float2 uv = ApplySpriteAnimation(scaledUV, g_division, g_draw_index);
    
    // 5. テクスチャサンプリングとマスク適用
    float4 mainColor = tex.Sample(texSampler, uv);
    mainColor *= marginMask; // 枠外を完全に透明化
    
    // 6. 元のカラー乗算と透過処理
    mainColor.rgb *= g_color;
    mainColor.a *= g_alpha;
    
    // ----------------------------------------------------
    // ★ 時間の周期化とマイルドなパルスのブレンド
    // ----------------------------------------------------
    float loopedTime = fmod(g_time * PULSE_SPEED, 6.283185f);
    
    float sinWave = sin(loopedTime);
    // 2乗(pow)のメリハリは維持しつつ、揺れ幅を抑えています
    float pulseFactor = pow(abs(sinWave), 2.0f) * sign(sinWave);
    
    // glowScale は「 0.85 ~ 1.15 」の間で優しく脈打ちます
    float glowScale = 1.0f + pulseFactor * PULSE_RANGE;

    // 7. 円形の後光を作成
    float dist = distance(localUV, float2(0.5, 0.5)) * (1.0f / glowScale);
    
    // 境界を綺麗に整えて強い光の輪郭を作ります
    float glowMask = smoothstep(0.5f, 0.20f, dist);
    float3 glowEffect = GLOW_COLOR * glowMask * GLOW_INTENSITY;
    
    // 8. 合成（アイテムの背後に後光を配置）
    float3 finalRGB = lerp(glowEffect * g_alpha, mainColor.rgb, mainColor.a);
    float finalAlpha = max(mainColor.a, glowMask * g_alpha);
    
    return float4(finalRGB, finalAlpha);
}