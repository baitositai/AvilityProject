#include "Animation.h"

Animation::Animation()
{
    animationIndex_ = -1;
    isLoop_ = false;
    isPlay_ = false;
	isNextLoop_ = false;
    type_ = TYPE::MAX;
    nextType_ = TYPE::MAX;
}

Animation::~Animation()
{
}

void Animation::Add(const std::string stringType, const int startIndex, const int endIndex, const float animationSpeed)
{
    // 対応表から検索
    auto it = animationNameMap_.find(stringType);

    // 対応する名前が見つからなかったら処理を抜ける
    if (it == animationNameMap_.end())
    {
        return;
    }

    TYPE type = it->second;

    // データの作成
    Data animationData = {};
    animationData.animationSpeed = animationSpeed;
    animationData.startIndex = startIndex;
    animationData.endIndex = endIndex;

    // 格納
    animationMap_[type] = std::move(animationData);
}

void Animation::Play(const TYPE type, const bool isLoop)
{

    const auto it = animationMap_.find(type);
    if (it != animationMap_.end())
    {
        type_ = type;
        isLoop_ = isLoop;
        isPlay_ = true;
        animationIndex_ = it->second.startIndex;
    }
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
    Play(nextType_, isNextLoop_);
   
    // 空にする
    nextType_ = TYPE::MAX;
}

void Animation::SetNextAnimationType(const TYPE nextType, const bool isNextLoop)
{
    nextType_ = nextType;
    isNextLoop_ = isNextLoop;
}

void Animation::SetAnimationSpeed(const std::string stringType, const float speed)
{
    // 対応表から検索
    auto it = animationNameMap_.find(stringType);

    // 対応する名前が見つからなかったら処理を抜ける
    if (it == animationNameMap_.end())
    {
        return;
    }

    TYPE type = it->second;

    animationMap_[type].animationSpeed = speed;
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