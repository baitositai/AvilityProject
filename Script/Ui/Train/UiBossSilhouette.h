#pragma once
#include "../UiBase.h"
#include "../../Manager/Game/EnemyTypes.h"

class EnemyManager;

class UiBossSilhouette :public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiBossSilhouette();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiBossSilhouette() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	// リソース用番号マップ
	const std::unordered_map<EnemyTypes::TYPE, int> RES_INDEX_MAP = 
	{
		{ EnemyTypes::TYPE::PANDA, 0},
		{ EnemyTypes::TYPE::MAID, 1},
		{ EnemyTypes::TYPE::GAIA_GOLEM, 2}
	};

	// 敵の管理参照
	EnemyManager& enemyManager_;

	// スプライト用ハンドル
	int* handles_;
};

