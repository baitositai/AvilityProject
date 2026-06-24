#pragma once
#include "../UiBase.h"
#include "../../Common/Vector2F.h"

class SceneManager;

class UiSpeechBubbleBase : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="followPos">追従位置</param>
	UiSpeechBubbleBase(const Vector2F& followPos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UiSpeechBubbleBase() override;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

protected:

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 追従座標
	const Vector2F& followPos_;

	// 相対位置
	Vector2F localPos_;

	// 拡大速度
	float scaleUpSpeed_;
};