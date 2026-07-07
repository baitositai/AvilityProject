// スプライトのUV座標を回転・反転・アスペクト比補正する関数
float2 CalculateSpriteUv(float2 inputUv, float2 graphSize, float2 division, float angle, float isReverseX, float isReverseY)
{
    // 中心を基準にするため一時的に中心をずらす
    float2 uv = inputUv - 0.5f;
    
    // テクスチャ全体の縦横比（アスペクト比）を計算
    float textureAspect = graphSize.x / graphSize.y;
    
    // テクスチャの分割比率を計算
    float divisionAspect = division.x / division.y;
    float finalAspect = textureAspect / divisionAspect;
    
    // 回転前にUVの歪みを補正して正方形にする
    uv.x *= finalAspect;
    
    // 回転
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    float2 rotatedUv;
    rotatedUv.x = uv.x * cosAngle + uv.y * sinAngle;
    rotatedUv.y = -uv.x * sinAngle + uv.y * cosAngle;
    uv = rotatedUv;
    
    // 補正していた倍率を元に戻す
    uv.x /= finalAspect;
    
    // 回転した後に反転処理を行う
    float2 reverseSign = float2(1.0f - 2.0f * isReverseX, 1.0f - 2.0f * isReverseY);
    uv *= reverseSign;
    
    // 中心を戻す
    uv += 0.5f;
    
    // はみ出さないようにクランプ処理
    uv = clamp(uv, 0.002f, 0.998f);
    
    return uv;
}

// アニメーションのコマ位置に合わせてUVを調整する関数
float2 ApplySpriteAnimation(float2 uv, float2 division, float drawIndex)
{
    // 1コマあたりのUVサイズを計算
    float2 size = 1.0f / division;
    
    // 描画番号から二次元配列の番号を計算
    float indexX = trunc(fmod(drawIndex, division.x));
    float indexY = trunc(drawIndex / division.x);
    float2 spriteIndex = float2(indexX, indexY);
    
    // 変形が終わったUVを1コマのサイズに縮小して目的のコマまで位置を調整
    return uv * size + (spriteIndex * size);
}