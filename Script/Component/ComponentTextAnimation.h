#pragma once
#include "../Common/CharacterString.h"

class SceneManager;
class SoundManager;

class ComponentTextAnimation
{
public:
	/// <summary>
	 /// コンストラクタ
	/// </summary>
	/// <param name="text">テキスト</param>
	/// <param name="charPerFrame">文字表示時間</param>
	ComponentTextAnimation(CharacterString& text, const float charPerFrame);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentTextAnimation();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了判定
	/// </summary>
	/// <returns>全てのテキスト文字を表示したらtrue,そうでない場合false</returns>
	bool IsEnd();

	/// <summary>
	/// 一瞬で文字を表示させる
	/// </summary>
	void Skip();

	/// <summary>
	/// 対象の文字列を設定
	/// </summary>
	/// <param name="text">文字列</param>
	void SetCharacterString(CharacterString& text);

	/// <summary>
	/// 文字表示されるまでのフレーム数
	/// </summary>
	/// <param name="charPerFrame"></param>
	void SetCharaPerFrame(const float charPerFrame);

private:

	// シーン管理クラス
	SceneManager& sceneManager_;

	// サウンド管理クラス
	SoundManager& soundManager_;

	// 元の文字列
	std::wstring textData_;

	// 文字列
	CharacterString text_;

	// 文字列の長さ
	int length_;

	// 現在表示されている文字数
	int charNum_;

	// 更新用ステップ
	float step_;

	// 1文字表示するまでのフレーム
	float charPerFrame_;
};