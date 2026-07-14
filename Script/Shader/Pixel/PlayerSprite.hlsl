#include "../common/Pixel/PixelShader2DHeader.hlsli"
#include "../common/Pixel/PixelShaderCommonFunction.hlsli"

Texture2D normalTex : register(t1);

cbuffer ConstantBuffer : register(b4)
{
    float3 g_color;
    float g_alpha;
    float2 g_division;
    float g_draw_index;
    float dummy;
    float4 g_outline_color;
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
    // 1. アニメーション適用後の正確なUVを取得
    float2 currentFrameUv = ApplySpriteAnimation(PSInput.uv, g_division, g_draw_index);
    float4 mainColor = tex.Sample(texSampler, currentFrameUv);
    
    // アウトライン処理（既存）
    float2 texelSize = (1.0f / g_division) * 0.005f;
    float alphaTop = tex.Sample(texSampler, currentFrameUv + float2(0.0f, -texelSize.y)).a;
    float alphaBottom = tex.Sample(texSampler, currentFrameUv + float2(0.0f, texelSize.y)).a;
    float alphaLeft = tex.Sample(texSampler, currentFrameUv + float2(-texelSize.x, 0.0f)).a;
    float alphaRight = tex.Sample(texSampler, currentFrameUv + float2(texelSize.x, 0.0f)).a;
    float maxNeighborAlpha = max(max(alphaTop, alphaBottom), max(alphaLeft, alphaRight));
    float outlineFactor = saturate(maxNeighborAlpha - mainColor.a);

    // --- ここから【超微小ボカシ】ドット絵専用なめらかライティング ---
    
    // 【修正の肝】巨大なテクスチャに対して大きすぎるボカシをかけるのをやめ、
    // 画面の1ピクセル未満の極めてわずかな微分値（0.2倍）だけで滑らかに補間させます。
    // これにより、キャラの形を一切崩さずに、ドットの角のジャギーだけが綺麗に消えます。
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
    
    // ドット絵本来の色味（服のグレーや斧の水色）を潰さないよう、
    // ライトの影響度を少しマイルド（0.5～1.2）にブレンドします
    //float lightingFactor = lerp(0.5f, 1.2f, ndl);
    
    // スペキュラ（左上の光沢ハイライト）
    // 法線が極小範囲で滑らかになったため、powを「5.0f」にすることで
    // ドットの形にならず、かつチカチカしない綺麗な光の筋がのります
    float specular = pow(ndl, 5.0f) * 0.6f;
    
    // カラー合成
    mainColor.rgb = (mainColor.rgb * g_color) + (float3(1.0f, 1.0f, 1.0f) * specular);
    //float gray = dot(mainColor.rgb, float3(0.299f, 0.587f, 0.114f));
    //mainColor.rgb = float3(gray, gray, gray);
    mainColor.rgb = saturate(mainColor.rgb);

    // --- ライティング処理ここまで ---

    // 透過・アウトライン合成
    mainColor.a *= g_alpha;
    mainColor.rgb = lerp(mainColor.rgb, g_outline_color.rgb, outlineFactor);
    mainColor.a = max(mainColor.a, maxNeighborAlpha * g_alpha);
    
    if (mainColor.a <= 0.0f)
        discard;
    
    return mainColor;
}