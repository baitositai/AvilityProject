#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Gimmick/AvilityBox.h"

#include "../../Object/../Parameter/ParameterActor.h"
#include "../../Object/../Parameter/Character/ParameterCharacter.h"
#include "../../Object/../Parameter/Gimmick/ParameterAvilityBox.h"

#include "../Common/Camera.h"
#include "../Common/SceneManager.h"
#include "StageManager.h"

void StageManager::Init()
{
	// ステージパラメータ
	std::unique_ptr<ParameterStage> parameter = std::make_unique<ParameterStage>();
	parameter->path_ = STAGE_PATH_MAP.at(type_);
	parameter->chipSize_ = Vector2(32, 32);
	parameter->hitIds_ = { 1 };

	// ステージ生成
	stage_ = std::make_unique<Stage>(std::move(parameter));
	stage_->Init();

}

void StageManager::Update()
{
	stage_->Update();
	//gimmick_->Update();
	for (const auto& gim : gimmick_)
	{
		gim->Update();
	}
	GimmickSweep();
}

void StageManager::Draw()
{
	stage_->Draw();
	//gimmick_->Draw();
	for (const auto& gim : gimmick_)
	{
		gim->Draw();
	}
}

void StageManager::ChageStage(const TYPE type)
{
	type_ = type;
	stage_->ChageStage(STAGE_PATH_MAP.at(type_));
}

void StageManager::DebugDraw()
{
	// タイルの仮描画
	/*for (int i = 0; i < tileNums_.x; i++)
	{
		for (int j = 0; j < tileNums_.y; j++)
		{
			tiles_[j][i]->DebugDraw();
		}
	}*/
	//gimmick_->DebugDraw();
	for (const auto& gim : gimmick_)
	{
		gim->DebugDraw();
	}
}

void StageManager::AddGimmick(CharacterBase& _chara, const int _boxNum)
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("PlayerParameter");
	const auto jsonParameter = jsonParameterMap.at("player").front();

	// Boxの追加処理
	//パラメーターの生成
	auto avParam = std::make_unique<ParameterAvilityBox>();
	avParam->Init();

	// 生成
	std::unique_ptr<AvilityBox> box = std::make_unique<AvilityBox>(std::move(avParam), _chara);
	// 初期化
	box->Init();

	gimmick_.push_back(std::move(box));
	




	//// 1. unique_ptr としてパラメータを生成するよう変更
	//auto avParam = std::make_unique<ParameterAvilityBox>();
	//avParam->hitSize_ = Vector2(48, 48);
	//avParam->gravityPower_ = 0.5f;
	//avParam->weight_ = 1.0f;
	//avParam->blastTime_ = 3.0f;
	//avParam->boxNum_ = _boxNum;

	//// ローカル座標をJsonで読み込み、プレイヤーの向きによって設置場所を変える
	//Vector2F localPos = { 50.0f, 50.0f };
	//const bool charaDir = _chara.GetParameter().direction_;
	//const Vector2F charaPos = _chara.GetParameter().pos_;

	//// ポインタ経由（->）でのアクセスに変更
	//avParam->placePos_ = charaDir ? Vector2F::SubVector2F(charaPos, localPos) : Vector2F::AddVector2F(charaPos, localPos);
	//std::vector<std::string> componentNameList = { "gravity", "move" };

	//// 2. std::move() を使って unique_ptr の所有権を渡す
	//std::unique_ptr<AvilityBox> avBox = std::make_unique<AvilityBox>(std::move(avParam), _chara);
	//avBox->Init();
	//gimmick_.push_back(std::move(avBox));
}

void StageManager::DeleteGimmick(void)
{
	//一番古いギミックを消す
	gimmick_.back()->SetIsDelete();
}

void StageManager::GimmickSweep()
{
	auto removeGim = std::remove_if(gimmick_.begin(), gimmick_.end(), [](std::unique_ptr<GimmickBase>& _gim)
		{
			return _gim->IsDelete();
		});
	gimmick_.erase(removeGim, gimmick_.end());
}

const Vector2& StageManager::GetStageSize() const
{
	return stage_->GetStageSize();
}

StageManager::StageManager()
{
	type_ = TYPE::NONE;
}

StageManager::~StageManager()
{
}