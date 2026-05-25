#include "../Parameter/ParameterActor.h"
#include "../Component/ComponentBase.h"
#include "ComponentGravity.h"

ComponentGravity::ComponentGravity(ActorBase& owner) :
	ComponentBase(owner),
    parameter_(owner.GetParameter())
{
}

ComponentGravity::~ComponentGravity()
{
}

void ComponentGravity::Update()
{
    const float gravity = owner_.GetGravityPowerWithBoost();
    const ParameterActor::DIR dir = parameter_.gravityDir_;
    const Vector2F dirNor = GRAVITY_DIR_MAP.at(dir);

    // 他のコンポーネントで計算された「下方向重力前提」の移動量
    Vector2F localMove = parameter_.moveAmount_;

    // ワールド座標系への変換用変数
    Vector2F worldMove = {};

    // 重力方向に応じて、ローカルの(横, 縦)をワールドの(X, Y)にマッピング
    // localMove.x = 左右移動, localMove.y = ジャンプ/落下
    switch (dir)
    {
    case ParameterActor::DIR::DOWN:
        worldMove.x = localMove.x;
        worldMove.y = localMove.y;
        break;
    case ParameterActor::DIR::UP:
        worldMove.x = -localMove.x; // 上下反転時は左右も反転させないと操作が逆になる
        worldMove.y = -localMove.y;
        break;
    case ParameterActor::DIR::RIGHT:
        worldMove.x = localMove.y; // ローカルの縦がワールドの横(X)になる
        worldMove.y = -localMove.x; // ローカルの横がワールドの縦(Y)になる
        break;
    case ParameterActor::DIR::LEFT:
        worldMove.x = -localMove.y;
        worldMove.y = localMove.x;
        break;
    }

    // 最後にワールド座標系で重力を加算する
    worldMove.x += dirNor.x * gravity;
    worldMove.y += dirNor.y * gravity;

    // 最終的な移動量を格納
    parameter_.moveAmount_ = worldMove;
}