#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Utility/UtilityCommon.h"
#include "UiExplanations.h"

UiExplanations::UiExplanations() :
    sceneManager_(SceneManager::GetInstance()),
    soundManager_(SoundManager::GetInstance())
{
	for (int i = 0; i < EXPLANATION_NUM; i++)
	{
		displayMap_.emplace(i, false);
	}
    moveStep_ = 0.0f;
	handles_ = nullptr;
	index_ = -1;
}

UiExplanations::~UiExplanations()
{
}

void UiExplanations::Init()
{
	handles_ = resourceManager_.GetHandles("explanations");
	pos_ = { (int)START_POS, POS_Y };
}

void UiExplanations::Update()
{
    if (update_)
    {
        update_();
    }
}

void UiExplanations::Draw()
{
    if (index_ != -1)
    {
        DrawRotaGraph(
            pos_.x,
            pos_.y,
            1.0f,
            0.0f,
            handles_[index_],
            true
        );
    }
}

void UiExplanations::Add(const TYPE type, const AvilityTypes::TYPE abilityType)
{
    int index = -1;

    // キーが存在するか判定してindexを取得
    if (type == TYPE::ABILITY)
    {
        auto it = INDEX_ABILITY_MAP.find(abilityType);
        if (it == INDEX_ABILITY_MAP.end())
        {
            return;
        }
        index = it->second;
    }
    else
    {
        auto it = INDEX_MAP.find(type);
        if (it == INDEX_MAP.end())
        {
            return;
        }
        index = it->second;
    }

    // 安全なアクセスと更新
    auto displayIt = displayMap_.find(index);
    if (displayIt == displayMap_.end())
    {
        return;
    }

    // 既に表示済みの場合
    if (displayIt->second)
    {
        // 一度全てのUIが表示されたかを確認
        bool isDelete = true;
        for (auto& ui : displayMap_)
        {
            if (!ui.second)
            {
                isDelete = false;
                break;
            }
        }
        if (isDelete) { Delete(); }

        return;
    }

    // フラグをオンにしてリストに追加
    displayIt->second = true;
    indexList_.push_back(index);

    // 処理開始の設定
    if (index_ == -1)
    {
        index_ = indexList_.front();
        indexList_.erase(indexList_.begin());
        update_ = std::bind(&UiExplanations::UpdateEnter, this);
        //soundManager_.PlaySe(SoundType::SE::DISPLAY_EXPLANATION);
    }
}

void UiExplanations::UpdateEnter()
{
    //時間更新
    moveStep_ += sceneManager_.GetDeltaTime();

    //座標計算
    pos_.x = static_cast<int>(UtilityCommon::EaseOutQuad(moveStep_, MOVE_TIME, START_POS, END_POS));

    if (pos_.x <= END_POS || moveStep_ > MOVE_TIME)
    {
        pos_.x = (int)END_POS;
        moveStep_ = 0.0f;
        update_ = std::bind(&UiExplanations::UpdateDisplay, this);
    }
}

void UiExplanations::UpdateDisplay()
{
    //時間更新
    moveStep_ += sceneManager_.GetDeltaTime();
    if (moveStep_ > DISPLAY_TIME)
    {
        moveStep_ = 0.0f;
        update_ = std::bind(&UiExplanations::UpdateExit, this);
    }
}

void UiExplanations::UpdateExit()
{
    //時間更新
    moveStep_ += sceneManager_.GetDeltaTime();

    //座標計算
    pos_.x = static_cast<int>(UtilityCommon::EaseOutQuad(moveStep_, MOVE_TIME, END_POS, START_POS));

    if (pos_.x >= START_POS || moveStep_ > MOVE_TIME)
    {
        pos_.x = (int)START_POS;
        moveStep_ = 0.0f;

        if (indexList_.empty())
        {
            index_ = -1;
            update_ = nullptr;
        }
        else
        {
            index_ = indexList_.front();
            indexList_.erase(indexList_.begin());
            update_ = std::bind(&UiExplanations::UpdateEnter, this);
            //soundManager_.PlaySe(SoundType::SE::DISPLAY_EXPLANATION);
        }
    }
}