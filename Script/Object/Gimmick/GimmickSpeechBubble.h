#pragma once
#include "GimmickBase.h"

class GimmickSpeechBubble : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickSpeechBubble(std::unique_ptr<ParameterGimmick> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickSpeechBubble() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 追従座標
	const Vector2F* followPos_;

	// 相対座標
	Vector2F localPos_;
};

