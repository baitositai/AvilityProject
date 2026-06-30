#pragma once
#include "../UiBase.h"

class EnemyBase;

class UiBossHpBar : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UiBossHpBar(EnemyBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiBossHpBar() override;

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

	// スプライト用HPバーインデックス
	static constexpr int HPBAR_NORMAL = 0;
	static constexpr int HPBAR_DAMAGE = 1;
	static constexpr int HPBAR_HEAL = 2;

	// HPバーの更新速度
	static constexpr float HPBAR_MOVE_SPEED = 0.5f;

	// 所有者
	EnemyBase& owner_;

	// 特別なHPバー番号
	int specialHpBarIndex_;

	// 前フレームHP
	int preHp_;

	// HPバー長さ
	int hpBarLength_;

	// 特別なHPバーの長さ
	float specialHpBarLength_;

	// HPバーハンドル
	int* hpBarHandles_;

	// HPバーサイズ
	Vector2 hpBarSize_;

	// HPバー位置
	Vector2 hpBarPos_;

	// ?バーの更新処理
	std::function<void()> updateHpBar_;

	// 特別なHPバーの更新
	void UpdateDamageBar();
	void UpdateHealBar();

	// 変更処理
	void ChangeDamageBar();
	void ChangeHealBar();
};

