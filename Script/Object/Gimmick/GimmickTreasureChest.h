#pragma once
#include "GimmickBase.h"
#include "../../Parameter/Gimmick/ParameterGimmickTreasureChest.h"

class GimmickTreasureChest : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	GimmickTreasureChest(std::unique_ptr<ParameterGimmickTreasureChest> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickTreasureChest() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// リソース取得
	/// </summary>
	void InitResource() override;

private:

	// パラメータ情報
	ParameterGimmickTreasureChest* parameterTreasureChest_;
};