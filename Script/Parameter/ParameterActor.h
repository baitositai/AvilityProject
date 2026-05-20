#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Object/Common/Animation.h"

// JSON名前空間
using Json = nlohmann::json;

class ParameterActor
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
	virtual ~ParameterActor();

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	virtual void LoadParameter(const Json& parameter);

	/// <summary>
	/// 重力方向をベクトル変換して返す
	/// </summary>
	/// <returns>重力方向のベクトル</returns>
	const Vector2F GetGravityDirectionVector() const;

	/// <summary>
	/// 現在の前方向のベクトルを返す
	/// </summary>
	/// <returns>前方向のベクトル</returns>
	const Vector2F GetFront() const;

	/// <summary>
	/// 現在の後方向のベクトルを返す
	/// </summary>
	/// <returns>後方向のベクトル</returns>
	const Vector2F GetBack() const;

	/// <summary>
	/// 現在の上方向のベクトルを返す
	/// </summary>
	/// <returns>上方向のベクトル</returns>	
	const Vector2F GetUp() const;

	/// <summary>
	/// 現在の下方向のベクトルを返す
	/// </summary>
	/// <returns>下方向のベクトル</returns>	
	const Vector2F GetDown() const;

	// テクスチャ
	int texture_;

	// スプライト用テクスチャ
	int* spriteTexture_;

	// 拡大率
	float scale_;

	// 角度
	float angle_;

	// 向き false 右 true 左
	bool direction_;

	// 透過判定
	bool transparent_;

	// 相対位置
	Vector2 localPos_;

	// 描画位置
	Vector2 drawPos_;

	// 分割数
	Vector2 divisionNum_;

	// 移動速度
	float moveSpeed_;

	// 移動速度上昇率
	float moveSpeedBoostRate_;

	// 位置
	Vector2F pos_;

	// 移動量
	Vector2F moveAmount_;

	// 重力
	float gravityPower_;

	// 重力の上昇値
	float gravityBoostRate_;

	// 重力方向
	DIR gravityDir_;

	// 物体の重み
	float weight_;

	// 地面判定
	bool isGround_;

	// 落下判定
	bool isFall_;

	// ヒットサイズ
	Vector2 hitSize_;

	// ヒット半径
	float hitRadius_;

	// リソース取得用のキー
	std::string resourceKey_;

	// コンポーネント用のキー配列
	std::vector<std::string> componentkeys_;

	// アニメーション用のマップ
	std::unordered_map<std::string, Animation::Data> animationDataMap_;

protected:
	
	// アニメーション情報の読み込み
	void LoadParameterAnimation(const Json& jsonParameter);
};