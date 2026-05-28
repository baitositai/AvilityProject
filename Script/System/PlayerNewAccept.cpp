#include "../Manager/Common/InputManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "PlayerNewAccept.h"

PlayerNewAccept::PlayerNewAccept() :
    inputManager_(InputManager::GetInstance())
{
    padList_.clear();
}

PlayerNewAccept::~PlayerNewAccept()
{
}

void PlayerNewAccept::Init(const int playerNum)
{
    // 参加人数が最大受付人数より小さい場合
    if (playerNum < PlayerManager::PLAYER_MAX)
    {
        for (int i = playerNum; i < PlayerManager::PLAYER_MAX; ++i)
        {
            int padValue = i + 1;
            padList_.push_back(padValue);
        }
    }
}

int PlayerNewAccept::IsNewPlayerAccept()
{
    if (padList_.empty()) { return -1; }

    for (auto& pad : padList_)
    {
        if (inputManager_.IsNew(InputManager::TYPE::ACCEPT_NEW_PLAYER, static_cast<Input::JOYPAD_NO>(pad)))
        {
            // 生成用に保持
            int ret = pad;

            // 一致した要素を検索してその要素だけを削除
            auto it = std::find(padList_.begin(), padList_.end(), pad);
            if (it != padList_.end())
            {
                padList_.erase(it);
            }

            // 入力あり
            return ret;
        }
    }

    // 入力なし
    return -1;
}