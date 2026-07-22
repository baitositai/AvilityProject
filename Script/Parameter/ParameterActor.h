#pragma once
#include <DxLib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "ParameterBase.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Object/Common/Animation.h"

class ParameterActor : public ParameterBase
{
public:	
	
	// 方向(重力用)
	enum class DIR
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,
		MAX
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterActor();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterActor() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	virtual void LoadParameter(const Json& parameter) override;

	/// <summary>
	/// ヒットサイズ合わせたスケールを返す
	/// </summary>
	/// <returns>当たり判定サイズに合わせたスケール</returns>
	Vector2 GetScaleToHitSize();

	/// <summary>
	/// 重力方向をベクトル変換して返す
	/// </summary>
	/// <returns>重力方向のベクトル</returns>
	Vector2F GetGravityDirectionVector();

	/// <summary>
	/// 現在の前方向のベクトルを返す
	/// </summary>
	/// <returns>前方向のベクトル</returns>
	Vector2F GetFront();

	/// <summary>
	/// 現在の後方向のベクトルを返す
	/// </summary>
	/// <returns>後方向のベクトル</returns>
	Vector2F GetBack();

	/// <summary>
	/// 現在の上方向のベクトルを返す
	/// </summary>
	/// <returns>上方向のベクトル</returns>	
	Vector2F GetUp();

	/// <summary>
	/// 現在の下方向のベクトルを返す
	/// </summary>
	/// <returns>下方向のベクトル</returns>	
	Vector2F GetDown();

	// 描画用情報
	int texture_;			// テクスチャ
	int* spriteTexture_;	// スプライト用テクスチャ
	float scale_;			// 拡大率
	float angle_;			// 角度
	float drawIndex_;		// 描画番号
	float alpha_;			// 透過値
	bool direction_;		// 向き false 右 true 左
	bool transparent_;		// 透過判定	
	Vector2 drawPos_;		// 描画位置
	Vector2 divisionNum_;	// 分割数	
	Vector2 drawSize_;		// 描画サイズ
	Vector2 drawHalfSize_;	// 描画ハーフサイズ
	VECTOR color_;			// 描画用カラー	
	std::string resourceKey_;// リソース取得用のキー

	// 物理挙動用情報	
	Vector2F pos_;			// 座標
	Vector2 localPos_;		// 相対位置	
	Vector2F moveAmount_;	// 移動量
	Vector2F knockBackPower_;// ノックバックパワー
	float weight_;			// 物体の重み
	bool isGround_;			// 地面判定	

	// ステータス情報
	int hp_;					// 体力
	int hpMax_;					// 最大体力	
	int attackPower_;			// 攻撃力
	float attackBoostRate_;		// 攻撃力上昇率
	float criticalRate_;		// クリティカル率
	float criticalDamageRate_;	// クリティカル時のダメージ上昇率
	float moveSpeed_;			// 移動速度
	float moveSpeedBoostRate_;	// 移動速度上昇率
	float gravityPower_;		// 重力
	float gravityBoostRate_;	// 重力の上昇値
	DIR gravityDir_;			// 重力方向

	// 衝突判定用情報
	float hitRadius_;		// ヒット半径
	Vector2 hitSize_;		// ヒットサイズ

	// コンポーネント用のキー配列
	std::vector<std::string> componentkeys_;

	// アニメーション用のマップ
	std::unordered_map<std::string, Animation::Data> animationDataMap_;

protected:
	
	// アニメーション情報の読み込み
	void LoadParameterAnimation(const Json& jsonParameter);
};