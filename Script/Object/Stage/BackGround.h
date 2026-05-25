#pragma once
#include <string>

class BackGround
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BackGround();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BackGround();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// リソースの設定
	/// </summary>
	/// <param name="key">リソース呼び出し用のキー</param>
	void SetResource(const std::string& key);

private:

	int img_;

};

