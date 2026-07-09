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