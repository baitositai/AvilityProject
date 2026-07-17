#pragma once
#include "../ActorBase.h"
#include "../../Parameter/Stage/ParameterStage.h"

class TileBase;

class Stage : public ActorBase
{

public:

	// リスト種類
	enum class LIST_TYPE
	{
		PLAYER_FIRST_POS,	// 初期位置
		BOSS_DOOR,			// ボス部屋ドア
		ENEMY_CREATE_AREA,	// 敵生成エリア
		ITEM_CREATE_AREA,	// アイテム生成エリア
		EVENT,				// イベント位置
		MAX
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit Stage(std::unique_ptr<ParameterStage> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Stage() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// ステージの変更
	/// </summary>
	/// <param name="stagePath">ステージパス</param>
	void ChageStage(const std::string& path = "");

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

	/// <summary>
	/// 指定したエリアリストを返す
	/// </summary>
	/// <param name="type">リスト種類</param>
	/// <returns>エリアリスト</returns>
	const std::vector<Vector2F>& GetAreaListMap(const LIST_TYPE type) const;

protected:

	// 型変換用のパラメータを返す関数
	ParameterStage* GetParameterStagePtr() { return parameterStage_; }

private:

	// リスト種類数
	static constexpr int LIST_TYPE_MAX = static_cast<int>(LIST_TYPE::MAX);

	// 生成位置インデックス
	static constexpr int LIST_TYPE_INDEXS[LIST_TYPE_MAX] = { 255, 256, 257, 258, 259 };
	const std::vector<int> PASS_PLATFORM_INDEXS = { 151, 152, 153 };

	// ステージサイズ
	Vector2 stageSize_;

	// タイル数
	Vector2 tileNums_;

	// パラメータ情報
	ParameterStage* parameterStage_;

	// タイルの配列
	std::vector<std::vector<std::unique_ptr<TileBase>>> tiles_;

	// 各種リストマップ
	std::unordered_map<LIST_TYPE, std::vector<Vector2F>> areaListMap_;

	// ステージの設定
	void SetStage();

	// ステージの初期化
	void ClearStage();

	// 描画範囲の取得
	void GetDrawRange(Vector2& rangeMin, Vector2& rangeMax);

	// 描画関係の初期化
	void InitDraw() override {};
};