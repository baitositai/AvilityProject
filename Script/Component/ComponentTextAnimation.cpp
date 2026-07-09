#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/SoundManager.h"
#include "ComponentTextAnimation.h"

ComponentTextAnimation::ComponentTextAnimation(CharacterString& text, const float charPerFrame) :
	text_(text),
	charPerFrame_(charPerFrame),
	sceneManager_(SceneManager::GetInstance()),
	soundManager_(SoundManager::GetInstance())
{
	textData_ = text_.string;
	step_ = 0.0f;
	charNum_ = 0;
	length_ = static_cast<int>(textData_.length());
}

ComponentTextAnimation::~ComponentTextAnimation()
{
}

void ComponentTextAnimation::Init()
{
	step_ = 0.0f;
	charNum_ = 0;
}

void ComponentTextAnimation::Update()
{
	// 文字数を達していた場合
	if (charPerFrame_ >= length_)
	{
		// 終了
		return;
	}

	// ステップの更新
	step_ += sceneManager_.GetDeltaTime();

	// 目標のフレーム数に達していた場合
	if (step_ > charPerFrame_)
	{
		// 一文字増やす
		charNum_++;

		// ステップを初期化
		step_ = 0.0f;

		// 効果音の再生
		//SoundManager::GetInstance().PlaySe(SoundType::SE::KEBOARD);
	}
}

void ComponentTextAnimation::Draw()
{
	// 現在の表示すべき文字列を取得
	text_.string = textData_.substr(0, charNum_);

	// 空の場合終了
	if (text_.string.empty())
	{
		return;
	}

	// 中央ぞろえで描画
	text_.DrawCenter();
}

bool ComponentTextAnimation::IsEnd()
{
	return charNum_ >= length_;
}

void ComponentTextAnimation::Skip()
{
	charNum_ = length_;
	step_ = 0.0f;
}

void ComponentTextAnimation::SetCharacterString(CharacterString& text)
{
	text_ = text;
	textData_ = text_.string;
	length_ = static_cast<int>(textData_.length());
	Init();
}

void ComponentTextAnimation::SetCharaPerFrame(const float charPerFrame)
{
	charPerFrame_ = charPerFrame;
}