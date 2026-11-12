#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Common/Animation.h"
#include "EnemyAzagrim.h"

EnemyAzagrim::EnemyAzagrim(std::unique_ptr<ParameterEnemyAzagrim> parameter) :
	EnemyBoss(std::move(parameter))
{
	//専用のパラメータ
	parameterEnemyAzagrim_ = dynamic_cast<ParameterEnemyAzagrim*>(GetParameterEnemyBossPtr());
	assert(parameterEnemyAzagrim_ != nullptr);
    timer_ = 0.0f;

}

EnemyAzagrim::~EnemyAzagrim()
{
}

void EnemyAzagrim::Init(void)
{
	EnemyBoss::Init();
    parameterEnemyAzagrim_->pos_ = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y + 20};
	animation_->Play(Animation::TYPE::IDLE, true);
}

void EnemyAzagrim::Update()
{
	EnemyBoss::Update();
}

void EnemyAzagrim::MobiusLoop()
{
    // 移動幅
    float moveWidth_ = 400.0f;
    float moveHeight_ = 200.0f;

	// 時間を進める
	timer_ += parameterEnemyAzagrim_->moveSpeed_ * scnMng_.GetDeltaTime();

    // 前フレームの位置
    float prevX = moveWidth_ * sinf(timer_);
    float prevY = moveHeight_ * sinf(timer_ * 2.0f);

    // 時間を進める
    timer_ += parameterEnemyAzagrim_->moveSpeed_ * scnMng_.GetDeltaTime();

    // 現在の位置
    float currentX = moveWidth_ * sinf(timer_);
    float currentY = moveHeight_ * sinf(timer_ * 2.0f);

    // 前フレームとの差分を移動量にする
    parameterEnemyAzagrim_->moveAmount_.x = currentX - prevX;
    parameterEnemyAzagrim_->moveAmount_.y = currentY - prevY;
}
