#pragma once
#include "../ActorBase.h"
#include "../../Parameter/Stage/ParameterStage.h"

class TileBase;

class Stage : public ActorBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit Stage(std::unique_ptr<ParameterStage> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stage() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ステージの変更
	/// </summary>
	/// <param name="stagePath">ステージパス</param>
	void ChageStage(const std::string& path);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

	/// <summary>
	/// ステージのサイズを返す
	/// </summary>
	/// <returns>ステージのサイズ</returns>
	const Vector2& GetStageSize() const { return stageSize_; }

	/// <summary>
	/// タイルの列数と行数を返す
	/// </summary>
	/// <returns>タイルの列数と行数</returns>
	const Vector2& GetTileNums() const { return tileNums_; }

private:

	// ステージサイズ
	Vector2 stageSize_;

	// タイル数
	Vector2 tileNums_;

	// パラメータ情報
	ParameterStage* parameterStage_;

	// タイルの配列
	std::vector<std::vector<std::unique_ptr<TileBase>>> tiles_;

	// タイル番号の配列(コライダー用)
	std::vector<std::vector<int>> chipIndexs_;

	// ステージの設定
	void SetStage();

	// ステージの初期化
	void ClearStage();

	// 描画範囲の取得
	void GetDrawRange(Vector2& rangeMin, Vector2& rangeMax);
};