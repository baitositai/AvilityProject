#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:

	struct Parameter : public CharacterBase::Parameter
	{
		Vector2 hitBoxSize;			// 衝突判定用ボックスサイズ
		Vector2 hitLocalPos;		// 衝突判定ボックスの相対位置
		Vector2F shotVec_;			// ショットベクトル
		float dashSpeed;			// ダッシュスピード
		float jumpPow;				// ジャンプ力
		float jumpPowMax;			// ジャンプ力の最大量
		bool isGround;				// 地面判定
		bool isFall;				// 落下判定
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="componentNameList">コンポーネント生成用名前リスト</param>
	Player(const Parameter& parameter, const std::vector<std::string> componentNameList);

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