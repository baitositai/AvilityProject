// アニメーションのコマ位置に合わせてUVを調整する関数
float2 ApplySpriteAnimation(float2 uv, float2 division, float drawIndex)
{
    // 1コマあたりのUVサイズを計算
    float2 size = 1.0f / division;
    
    // 整数型にキャストしてインデックスを正確に計算
    int index = (int) drawIndex;
    int divX = (int) division.x;
    
    // 二次元配列のインデックスを算出
    float indexX = (float) (index % divX);
    float indexY = (float) (index / divX);
    float2 spriteIndex = float2(indexX, indexY);
    
    // 変形が終わったUVを1コマのサイズに縮小して目的のコマまで位置を調整
    return uv * size + (spriteIndex * size);
}