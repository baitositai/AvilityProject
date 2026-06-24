#pragma once
#include "UiGameBase.h"
#include "../../Common/IntVector3.h"

class SceneManager;

class UiDamage : public UiGameBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	/// <param name="pos">座標</param>
	UiDamage(const int damage, const Vector2& pos, const IntVector3& color);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiDamage() override;

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

private:

	// 移動速度
	static constexpr float MOVE_SPEED = 0.08f;

	// α値変更速度
	static constexpr float ALPHA_SPEED = 5.0f;

	// 削除時間
	static constexpr float DELETE_TIME = 3.0f;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// ダメージ位置
	Vector2F damagePos_;

	// 色
	IntVector3 color_;

	// α値
	float alpha_;

	// 時間
	float timer_;
};