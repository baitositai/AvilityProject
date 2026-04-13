#pragma once
#include <memory>
#include "../ActorBase.h"

class TileBase;

class Stage : public ActorBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stage(const std::string& path);

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
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// タイルの配列
	std::vector<std::vector<std::unique_ptr<TileBase>>> tiles_;
};

