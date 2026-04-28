#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:

	struct Parameter : public CharacterBase::Parameter
	{
		Vector2F defaultAttackLocalPos = {};// 通常攻撃の当たり判定調整座標	
		Vector2F shotVec_;					// ショットベクトル
		float defaultAttackRadius = 0.0f;	// 通常攻撃の範囲半径
		float dashSpeed = 0.0f;				// ダッシュスピード

		// アニメーション関係
		int animationsIdle = -1;			// 待機アニメーション数
		int animationsWalk = -1;			// 移動アニメーション
		int animationsBrake = -1;			// ブレーキアニメーション
		int animationsAttack = -1;			// 攻撃アニメーション
		int animationsJump = -1;			// ジャンプアニメーション
		int animationsFall = -1;			// 落下アニメーション
		int animationsDie = -1;				// 死亡アニメーション
		int animationsDamage = -1;			// ダメージアニメーション
		int animationsPause = -1;			// ポーズアニメーション
		float animationAttackSpeed = 0.0f;	// 攻撃アニメーション速度
	};

	// アニメーション種類
	enum class ANIMATION
	{
		IDLE = 0,
		WALK = 1,
		BRAKE = 2,
		ATTACK = 3,
		JUMP = 4,
		FALL = 5,
		DIE = 6,
		DAMAGE = 7,
		PAUSE = 8,
		MAX
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="stateComponentNameList">状態別コンポーネント生成リスト</param>
	/// <param name="defaultComponentNameList">通常コンポーネント生成リスト</param>
	/// <param name="animation">アニメーション</param>
	Player(
		const Parameter& parameter, 
		const std::unordered_map<std::string, std::string> stateComponentNameList,
		const std::vector<std::string> defaultComponentNameList = {},
		std::unique_ptr<Animation> animation = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

	/// <summary>
	/// ショットベクトルの設定
	/// </summary>
	/// <param name="shotVec">ショットベクトル</param>
	void SetShotVec(const Vector2F shotVec) { parameter_.shotVec_ = shotVec; }

	/// <summary>
	/// ショットベクトル（parameter_.shotVec_）を取得して返します。
	/// </summary>
	/// <returns>parameter_.shotVec_ のコピーを Vector2F 型で返します。メソッド自体はオブジェクトを変更しません（const）。</returns>
	const Vector2F GetShotVec() const { return parameter_.shotVec_; }

	/// <summary>
	/// 通常攻撃の位置を調整する座標を返す
	/// </summary>
	/// <returns>通常攻撃の相対座標</returns>
	const Vector2F GetDefaultAttackLocalPos() const { return parameter_.defaultAttackLocalPos; }

	/// <summary>
	/// ダッシュ速度を返す
	/// </summary>
	/// <returns>ダッシュ速度</returns>
	const float GetDashSpeed() const { return parameter_.dashSpeed; }

	/// <summary>
	/// 通常攻撃の範囲半径を返す
	/// </summary>
	/// <returns>通常攻撃の範囲半径</returns>
	const float GetDefaultAttackRadius() const { return parameter_.defaultAttackRadius; }
	
private:

	// パラメータ情報
	Parameter parameter_;
};