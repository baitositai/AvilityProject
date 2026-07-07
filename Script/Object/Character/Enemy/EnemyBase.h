#pragma once
#include "../CharacterBase.h"
#include "../../../Parameter/Character/Enemy/ParameterEnemy.h"

class ParameterEnemy;

class EnemyBase : public CharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyBase(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyBase() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// 敵の描画
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// アイテムの生成
	/// </summary>
	virtual void DropItem();

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage"></param>
	void Damage(const int damage, const Vector2& hitPos = {}) override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEnemy& GetParameter() { return *parameterEnemy_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterEnemy& GetParameter() const { return *parameterEnemy_; }

protected:

	// ダメージ描画のステップの最大値
	static constexpr float DAMAGE_DRAW_STEP_MAX = 0.3f;

	// ダメージ時の描画用ステップ
	float damageDrawStep_;

	// 型変換用のパラメータを返す関数
	ParameterEnemy* GetParameterEnemyPtr() { return parameterEnemy_; }

private:

	// 定数バッファ―サイズ
	static constexpr int CONST_BUFFER_SIZE = 4;

	// キャラクターのパラメータ
	ParameterEnemy* parameterEnemy_;

	// 描画初期化処理
	virtual void InitDraw() override;
};