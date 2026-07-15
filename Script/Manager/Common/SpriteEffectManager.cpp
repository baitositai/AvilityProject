#include "../../Manager/Common/ResourceManager.h"
#include "../../Resource/ResourceTexture.h"
#include "../../Object/ActorBase.h"
#include "../../Object/Effect/EffectBase.h"
#include "../../Object/Effect/EffectTargetFollow.h"
#include "SpriteEffectManager.h"

void SpriteEffectManager::Init()
{
	for (auto& effect : effectList_)
	{
		effect->Init();
	}

	nextId_ = 0;
}

void SpriteEffectManager::Update()
{
	for (auto& effect : effectList_)
	{
		effect->Update();
	}
}

void SpriteEffectManager::Draw()
{
	for (auto& effect : effectList_)
	{
		effect->Draw();
	}
}

void SpriteEffectManager::DebugDraw()
{
	for (auto& effect : effectList_)
	{
		effect->DebugDraw();
	}
}

void SpriteEffectManager::Add(std::unique_ptr<EffectBase> effect)
{
	// 初期化
	effect->Init();

	// 追加
	effectList_.emplace_back(std::move(effect));
}

int SpriteEffectManager::Create(const CreateParameter createParameter)
{	
	nextId_++;

	// パラメータ定義
	std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();

	// パラメータ設定
	parameter->pos_ = createParameter.pos;
	parameter->angle_ = createParameter.angle;
	parameter->scale_ = createParameter.scale;
	parameter->resourceKey_ = createParameter.resourceKey;
	parameter->direction_ = createParameter.direction;
	parameter->isLoop_ = createParameter.isLoop;
	parameter->transparent_ = true;
	parameter->componentkeys_ = { "spriteAnimation" };
	parameter->id_ = nextId_;

	// アニメーション数が指定されてない場合
	int animationNum = createParameter.animationNum;
	if (animationNum <= -1)
	{
		// アニメーション数を取得
		const Vector2 animationDiv = ResourceManager::GetInstance().GetResourceTexture(parameter->resourceKey_)->GetDivsion();
		animationNum = animationDiv.x * animationDiv.y;
	}

	// アニメーション設定
	parameter->animationDataMap_.emplace("effect", Animation::Data{0, animationNum - 1, createParameter.animationSpeed});

	// ターゲットがいる場合
	if (createParameter.target)
	{
		// ターゲットの設定
		std::unique_ptr<EffectTargetFollow> effectTarget = std::make_unique<EffectTargetFollow>(std::move(parameter));
		effectTarget->SetTarget(createParameter.target);
		
		// 格納
		effectList_.push_back(std::move(effectTarget));
	}
	else
	{
		// エフェクト生成
		std::unique_ptr<EffectBase> effect = std::make_unique<EffectBase>(std::move(parameter));

		// 格納
		effectList_.push_back(std::move(effect));
	}

	// エフェクト初期化
	effectList_.back()->Init();

	return nextId_;
}

void SpriteEffectManager::Delete(const int id)
{
	auto iterator = std::find_if(effectList_.begin(), effectList_.end(), [id](const auto& effect)
		{
			return effect->GetParameter().id_ == id;
		});

	if (iterator != effectList_.end())
	{
		(*iterator)->Delete();
	}
}

void SpriteEffectManager::Clear()
{
	effectList_.clear();
}

void SpriteEffectManager::Sweep()
{
	auto it = std::remove_if(effectList_.begin(), effectList_.end(),
		[](const std::unique_ptr<EffectBase>& effect)
		{
			return effect->IsDelete();
		});

	effectList_.erase(it, effectList_.end());
}

SpriteEffectManager::SpriteEffectManager()
{
	nextId_ = -1;
}

SpriteEffectManager::~SpriteEffectManager()
{
}