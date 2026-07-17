#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Render/PixelMaterial.h"
#include "../Render/PixelRenderer.h"
#include "Fader.h"

Fader::Fader()
{
	// 初期化
	state_ = STATE::NONE;
	alpha_ = -1;
	isPreEnd_ = false;
	isEnd_ = false;
	fadeImage_ = -1;

	// 各種処理の登録
	RegisterStateSetFunction(STATE::NONE, std::bind(&Fader::SetNone, this));
	RegisterStateSetFunction(STATE::IMMEDIATE, std::bind(&Fader::SetImmediate, this));
	RegisterStateSetFunction(STATE::FINISH, std::bind(&Fader::SetFinish, this));
	RegisterStateSetFunction(STATE::FADE_IN, std::bind(&Fader::SetFadeIn, this));
	RegisterStateSetFunction(STATE::FADE_OUT, std::bind(&Fader::SetFadeOut, this));
}

Fader::~Fader()
{
	DeleteGraph(fadeImage_);
}

void Fader::Init()
{
	SetFade(STATE::NONE);

	// マテリアルの生成
	material_ = std::make_unique<PixelMaterial>(ResourceManager::GetInstance().GetHandle("Fade"), 1);

	// テクスチャの設定
	fadeImage_ = LoadGraph(L"Resource/Image/Fade/136.png");
	//material_->AddTextureBuf(parameter_->texture_);
	material_->AddTextureBuf(fadeImage_);

	// バッファーの設定
	//material_->AddConstBuf(FLOAT4{ parameter_->color_.x, parameter_->color_.y,parameter_->color_.z, parameter_->alpha_ });
	material_->AddConstBuf(FLOAT4{ 0.0f, 0.0f,0.0f, 0.0f });

	// レンダラーの生成
	renderer_ = std::make_unique<PixelRenderer>(*material_);
}

void Fader::Update()
{
	// 終了している場合
	if (isEnd_)
	{
		// 何もしない
		return;
	}

	// 状態ごとの更新処理
	update_();	
}

void Fader::Draw()
{
	// 状態ごとの描画処理
	draw_();
}

void Fader::SetFade(const STATE state)
{
	// 状態を設定
	state_ = state;

	// 状態ごとの処理を実行
	setMap_[state]();
}

void Fader::RegisterStateSetFunction(const STATE state, const std::function<void()> function)
{
	setMap_[state] = function;
}

void Fader::SetNone()
{
	alpha_ = MAX_ALPHA;
	isPreEnd_ = true;
	isEnd_ = true;

	// 処理の登録
	update_ = std::bind(&Fader::UpdateNone, this);
	draw_ = std::bind(&Fader::DrawNone, this);
}

void Fader::SetFadeOut()
{
	alpha_ = 0;
	isPreEnd_ = false;
	isEnd_ = false;

	// 処理の登録
	update_ = std::bind(&Fader::UpdateFadeOut, this);
	draw_ = std::bind(&Fader::DrawFade, this);
}

void Fader::SetFadeIn()
{
	alpha_ = MAX_ALPHA;
	isPreEnd_ = false;
	isEnd_ = false;

	// 処理の登録
	update_ = std::bind(&Fader::UpdateFadeIn, this);
	draw_ = std::bind(&Fader::DrawFade, this);
}

void Fader::SetImmediate()
{
	alpha_ = MAX_ALPHA;
	isPreEnd_ = true;
	isEnd_ = true;

	// 処理の登録
	update_ = std::bind(&Fader::UpdateNone, this);
	draw_ = std::bind(&Fader::DrawNone, this);
}

void Fader::SetFinish()
{
	alpha_ = 0;
	isPreEnd_ = true;
	isEnd_ = true;

	// 処理の登録
	update_ = std::bind(&Fader::UpdateNone, this);
	draw_ = std::bind(&Fader::DrawNone, this);
}

void Fader::UpdateFadeOut()
{
	alpha_ += SPEED_ALPHA;
	if (alpha_ > MAX_ALPHA)
	{
		// フェード終了
		alpha_ = MAX_ALPHA;
		if (isPreEnd_)
		{
			// 1フレーム後(Draw後)に終了とする
			isEnd_ = true;
		}
		isPreEnd_ = true;
	}
}

void Fader::UpdateFadeIn()
{
	alpha_ -= SPEED_ALPHA;
	if (alpha_ < 0)
	{
		// フェード終了
		alpha_ = 0;
		if (isPreEnd_)
		{
			// 1フレーム後(Draw後)に終了とする
			isEnd_ = true;
		}
		isPreEnd_ = true;
	}
}

void Fader::DrawFade() const
{
	/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/

	// メッシュ生成
	renderer_->MakeSquereVertex(Vector2(Application::SCREEN_SIZE_X/2, Application::SCREEN_SIZE_Y/2)
		, Vector2(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y));

	// 定数バッファの更新
	material_->SetConstBuf(0, FLOAT4{ 0.0f,0.0f,0.0f,alpha_ / MAX_ALPHA });

	// 描画処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	renderer_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
