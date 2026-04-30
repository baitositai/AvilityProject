#include "Animation.h"

Animation::Animation()
{
    animationIndex_ = -1;
    isLoop_ = false;
    isPlay_ = false;
    type_ = TYPE::MAX;
    nextType_ = TYPE::MAX;
}

Animation::~Animation()
{
}

void Animation::Add(const std::string stringType, const int startIndex, const int endIndex, const float animationSpeed)
{
    // 1. 対応表から TYPE を検索する
    auto it = animationNameMap_.find(stringType);

    // 対応する名前が見つからなかったら処理を抜ける
    if (it == animationNameMap_.end())
    {
        return;
    }

    TYPE type = it->second;

    // 2. データの作成
    Data animationData = {};
    animationData.animationSpeed = animationSpeed;
    animationData.startIndex = startIndex;
    animationData.endIndex = endIndex;

    // 3. unordered_map に格納 (std::move を忘れずに)
    animationMap_.emplace(type, std::move(animationData));
}

void Animation::Play(const TYPE type, const bool isLoop)
{
	type_ = type;
	isLoop_ = isLoop;
	isPlay_ = true;
}

void Animation::Stop()
{
	isPlay_ = false;
}

void Animation::CheckNextAnimation()
{
    // 指定されていない場合
    if (nextType_ == TYPE::MAX)
    {
        // 無視
        return;
    }

    // 再生
    Play(nextType_);
   
    // 空にする
    nextType_ = TYPE::MAX;
}

const Animation::Data Animation::GetAnimationData() const
{
    // 現在の種類のデータがあるか探索
    auto it = animationMap_.find(type_);

    // キーが存在しない場合
    if (it == animationMap_.end())
    {
		// 空の構造体を返す
        return Data();
    }

    // 中身を返す
    return it->second;
}