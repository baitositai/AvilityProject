#pragma once
#include "ParameterGimmick.h"

class ParameterAvilityBox : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterAvilityBox();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterAvilityBox() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

	//ボックスの当たり判定のローカル座標
	Vector2 hitLocalPos_;	

	//設置時のプレイヤーとのローカル座標
	Vector2F placePos_;		
	
	//爆発するまでの時間
	float blastTime_;		

	//何個目のボックスか
	int boxNum_;				

};