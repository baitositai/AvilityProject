#include "../common/Pixel/PixelShader2DHeader.hlsli"
#include "../common/Pixel/PixelShaderCommonFunction.hlsli"

Texture2D normalTex : register(t1);

cbuffer ConstantBuffer : register(b4)
{
    float3 g_color;
    float g_alpha;
    float2 g_division;
    float g_draw_index;
    float g_time;
    float3 g_outline_color;
    float isMetal;
    float isSuper;
    float3 g_dummy;
 
};

// 後光（バックグロー）の設定
static const float3 GLOW_COLOR = float3(0.3f, 0.9f, 1.0f); // 後光の色（シアン・水色）
static const float GLOW_INTENSITY = 4.0f; // 後光の明るさ

// ★後光の太さ（ここを大きく引き上げました！元の 0.012f → 0.035f）
static const float GLOW_THICKNESS = 0.035f;

// アニメーションのスピードと変化幅
static const float PULSE_SPEED = 8.0f;
static const float PULSE_RANGE = 0.15f; // パルスによる太さの伸縮幅

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 1. 元のUV（0.0 ~ 1.0）
    float2 localUV = PSInput.uv;
    
    // 2. アニメーション適用後の正確なUVを取得
    float2 currentFrameUv = ApplySpriteAnimation(localUV, g_division, g_draw_index);
    
    // 3. 元のテクスチャサンプリング
    float4 mainColor = tex.Sample(texSampler, currentFrameUv);
    
    // 4. キャラ本来のアウトライン処理（既存）
    float2 texelSize = (1.0f / g_division) * 0.005f;
    float alphaTop = tex.Sample(texSampler, currentFrameUv + float2(0.0f, -texelSize.y)).a;
    float alphaBottom = tex.Sample(texSampler, currentFrameUv + float2(0.0f, texelSize.y)).a;
    float alphaLeft = tex.Sample(texSampler, currentFrameUv + float2(-texelSize.x, 0.0f)).a;
    float alphaRight = tex.Sample(texSampler, currentFrameUv + float2(texelSize.x, 0.0f)).a;
    float maxNeighborAlpha = max(max(alphaTop, alphaBottom), max(alphaLeft, alphaRight));
    float outlineFactor = saturate(maxNeighborAlpha - mainColor.a);

    // --- 【超微小ボカシ】ドット絵専用なめらかライティング ---
    float2 dx = ddx(currentFrameUv) * 0.2f;
    float2 dy = ddy(currentFrameUv) * 0.2f;
    float4 normalMapColor = normalTex.SampleGrad(texSampler, currentFrameUv, dx, dy);
    
    // 法線ベクトル変換
    float3 normal = normalMapColor.rgb * 2.0f - 1.0f;
    normal = normalize(normal);
    
    // 光源（左上から）
    float3 lightDir = normalize(float3(-1.0f, -1.0f, 1.2f));
    
    // ディフューズ（陰影）の計算
    float ndl = saturate(dot(normal, lightDir));
    
    // スペキュラ（左上の光沢ハイライト）
    float specular = pow(ndl, 5.0f) * 0.6f;
    
    // カラー合成
    mainColor.rgb = (mainColor.rgb * g_color) + (float3(1.0f, 1.0f, 1.0f) * specular);
    
    if (isMetal >= 1.0f)
    {
        float gray = (mainColor.r + mainColor.g + mainColor.b) / 3.0f;
        gray *= 2.0f;
        mainColor.rgb = float3(gray, gray, gray);
    }
    
    // 彩度を保つために、saturateで0～1の範囲にとどめる
    mainColor.rgb = saturate(mainColor.rgb);

    // --- ライティング処理ここまで ---

    // 透過・アウトライン合成
    float charAlpha = mainColor.a * g_alpha;
    float3 charRGB = lerp(mainColor.rgb, g_outline_color, outlineFactor);
    float finalCharAlpha = max(charAlpha, maxNeighborAlpha * g_alpha);

    if (isSuper >= 1.0f)
    {
        // ----------------------------------------------------
        // ★ キャラクターの形に沿った後光（シルエット型）の計算
        // ----------------------------------------------------
        float loopedTime = fmod(g_time * PULSE_SPEED, 6.283185f);
        float sinWave = sin(loopedTime);
        float pulseFactor = pow(abs(sinWave), 2.0f) * sign(sinWave);
    
        // 伸縮するオフセット幅
        float currentThickness = GLOW_THICKNESS * (1.0f + pulseFactor * PULSE_RANGE);
        float2 glowOffset = (1.0f / g_division) * currentThickness;

        // 【12方向サンプリング】
        // A. キャラクターのキワ（隙間）を埋めるための近距離サンプリング（内周4方向）
        float2 innerOffset = glowOffset * 0.4f;
        float i1 = tex.Sample(texSampler, currentFrameUv + float2(0.0f, -innerOffset.y)).a;
        float i2 = tex.Sample(texSampler, currentFrameUv + float2(0.0f, innerOffset.y)).a;
        float i3 = tex.Sample(texSampler, currentFrameUv + float2(-innerOffset.x, 0.0f)).a;
        float i4 = tex.Sample(texSampler, currentFrameUv + float2(innerOffset.x, 0.0f)).a;
        float innerGlow = (i1 + i2 + i3 + i4) * 0.25f;

        // B. 大きく外側へ広げるための遠距離サンプリング（外周8方向）
        float o1 = tex.Sample(texSampler, currentFrameUv + float2(0.0f, -glowOffset.y)).a;
        float o2 = tex.Sample(texSampler, currentFrameUv + float2(0.0f, glowOffset.y)).a;
        float o3 = tex.Sample(texSampler, currentFrameUv + float2(-glowOffset.x, 0.0f)).a;
        float o4 = tex.Sample(texSampler, currentFrameUv + float2(glowOffset.x, 0.0f)).a;
    
        float o5 = tex.Sample(texSampler, currentFrameUv + float2(-glowOffset.x * 0.7f, -glowOffset.y * 0.7f)).a;
        float o6 = tex.Sample(texSampler, currentFrameUv + float2(glowOffset.x * 0.7f, -glowOffset.y * 0.7f)).a;
        float o7 = tex.Sample(texSampler, currentFrameUv + float2(-glowOffset.x * 0.7f, glowOffset.y * 0.7f)).a;
        float o8 = tex.Sample(texSampler, currentFrameUv + float2(glowOffset.x * 0.7f, glowOffset.y * 0.7f)).a;
        float outerGlow = (o1 + o2 + o3 + o4 + o5 + o6 + o7 + o8) * 0.125f;

        // 内周と外周をブレンドして、滑らかで繋がったグラデーション後光を作成
        float glowMask = max(innerGlow, outerGlow);
    
        // pow の値を下げて (1.5 -> 1.0) 光の減衰をなだらかにし、より広く大きく見えるようにします
        glowMask = saturate(pow(glowMask, 1.0f));
    
        // g_outline_color を白と混ぜて淡い色にする
        float colorSoftness = 0.5f; // 0.0で元の色、1.0で完全に白（0.3～0.6程度で調整）
        //float3 softGlowColor = lerp(g_outline_color, float3(1.0f, 1.0f, 1.0f), colorSoftness);
        float3 softGlowColor = float3(0.8f,0.8f,0.8f);

        // 乗算する強度（GLOW_INTENSITY）も少し抑えめに調整できるように分離
        float currentGlowIntensity = 2.0f; // 元の 4.0f から少し下げることで濃さを抑制
        
        float3 glowEffect = softGlowColor * glowMask * currentGlowIntensity;
    
        // ----------------------------------------------------
        // ★ 最終合成
        // ----------------------------------------------------
        float3 finalRGB = lerp(glowEffect * g_alpha, charRGB, finalCharAlpha);
        float finalAlpha = max(finalCharAlpha, glowMask * g_alpha);
    
        if (finalAlpha <= 0.0f)
            discard;
        
        return float4(finalRGB, finalAlpha); 
    }
    
    if (finalCharAlpha <= 0.0f)
        discard;
        
    return float4(charRGB, finalCharAlpha);

}