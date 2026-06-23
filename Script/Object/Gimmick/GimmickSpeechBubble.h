#pragma once
#include "GimmickBase.h"
#include "../../Parameter/Gimmick/ParameterGimmickSpeechBubble.h"

class GimmickSpeechBubble : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickSpeechBubble(std::unique_ptr<ParameterGimmickSpeechBubble> parameter);

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

	/// <summary>
	/// 吹き出しの設定
	/// </summary>
	/// <param name="followPos">追従座標</param>
	/// <param name="resourceName">リソース名</param>
	/// <param name="displayTime">表示時間</param>
	void Set(const Vector2F* followPos, const std::string& resourceName, const float displayTime);

private:

	// パラメータ情報
	ParameterGimmickSpeechBubble* parameterSpeechBubble_;

	// 追従座標
	const Vector2F* followPos_;

	// タイマー
	float timer_;
};