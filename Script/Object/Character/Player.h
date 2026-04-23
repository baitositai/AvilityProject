#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:

	struct Parameter : public CharacterBase::Parameter
	{
		Vector2 hitBoxSize = {};			// 衝突判定用ボックスサイズ
		Vector2F shotVec_;					// ショットベクトル
		float dashSpeed = 0.0f;				// ダッシュスピード
		float jumpPow = 0.0f;				// ジャンプ力
		float jumpPowMax = 0.0f;			// ジャンプ力の最大量
		bool isGround = false;				// 地面判定
		bool isFall = false;				// 落下判定

		// アニメーション関係
		int animationsIdle;					// 待機アニメーション数
		int animationsWalk;					// 移動アニメーション
		int animationsBrake;				// ブレーキアニメーション
		int animationsAttack;				// 攻撃アニメーション
		int animationsJump;					// ジャンプアニメーション
		int animationsFall;					// 落下アニメーション
		int animationsDie;					// 死亡アニメーション
		int animationsDamage;				// ダメージアニメーション
		int animationsPause;				// ポーズアニメーション
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
	Player(const Parameter& parameter, const std::unordered_map<std::string, std::string> stateComponentNameList, const std::vector<std::string> defaultComponentNameList = {});

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
	/// アニメーションの初期化
	/// </summary>
	void InitAnimation() override;

	/// <summary>
	/// アニメーションの変更
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="isLoop">ループ判定</param>
	void ChangeAnimation(const ANIMATION type, const bool isLoop = true);

	/// <summary>
	/// ショットベクトルの設定
	/// </summary>
	/// <param name="shotVec">ショットベクトル</param>
	void SetShotVec(const Vector2F shotVec) { parameter_.shotVec_ = shotVec; }

	/// <summary>
	/// 地面判定の設定
	/// </summary>
	/// <param name="isGround">地面判定</param>
	void SetIsGround(const bool isGround) { parameter_.isGround = isGround; }

	/// <summary>
	/// 落下判定の設定
	/// </summary>
	/// <param name="isFall">落下判定</param>
	void SetIsFall(const bool isFall) { parameter_.isGround = isFall; }

	/// <summary>
	/// 最大ジャンプ力を設定
	/// </summary>
	/// <param name="jumpPowMax">最大ジャンプ力</param>
	void SetJumpPowMax(const float jumpPowMax) { parameter_.jumpPow = jumpPowMax; }

	/// <summary>
	/// 衝突する範囲を返す
	/// </summary>
	/// <returns>衝突する範囲</returns>
	const Vector2& GetHitBoxSize() const { return parameter_.hitBoxSize; }

	/// <summary>
	/// ショットベクトル（parameter_.shotVec_）を取得して返します。
	/// </summary>
	/// <returns>parameter_.shotVec_ のコピーを Vector2F 型で返します。メソッド自体はオブジェクトを変更しません（const）。</returns>
	const Vector2F GetShotVec() const { return parameter_.shotVec_; }

	/// <summary>
	/// 最大ジャンプ力を返す
	/// </summary>
	/// <returns>ジャンプ力</returns>
	const float GetJumpPow() const { return parameter_.jumpPow; }

	/// <summary>
	/// 最大ジャンプ力を返す
	/// </summary>
	/// <returns>最大ジャンプ力</returns>
	const float GetJumpPowMax() const { return parameter_.jumpPowMax; }

	/// <summary>
	/// ダッシュ速度を返す
	/// </summary>
	/// <returns>ダッシュ速度</returns>
	const float GetDashSpeed() const { return parameter_.dashSpeed; }

	/// <summary>
	/// 地面判定を返す
	/// </summary>
	/// <returns>地面判定</returns>
	const bool IsGround() const { return parameter_.isGround; }

	/// <summary>
	/// 落下判定を返す
	/// </summary>
	/// <returns>落下判定</returns>
	const bool IsFall() const { return parameter_.isFall; }
	
private:

	// パラメータ情報
	Parameter parameter_;
};