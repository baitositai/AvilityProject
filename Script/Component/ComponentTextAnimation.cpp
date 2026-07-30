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
	// 全ての文字を表示し切っている場合は何もしない
	if (charNum_ >= length_)
	{
		return;
	}

	// ステップの更新
	step_ += sceneManager_.GetDeltaTime();

	// 1文字進める時間を超えた場合
	if (step_ >= charPerFrame_)
	{
		// 一文字増やす
		charNum_++;

		// 余分に経過した時間を持ち越して初期化
		step_ -= charPerFrame_;

		// 効果音の再生
		soundManager_.PlaySe(SoundType::SE::TEXT_ANIMATION);
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
	text_.DrawFormatCenter();
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