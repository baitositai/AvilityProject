#pragma once
#include "../ActorBase.h"

class Stage : public ActorBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stage();

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
	void DebugDraw() override;

private:

	// ステージのパス
	const std::wstring PATH_STAGE;

};

