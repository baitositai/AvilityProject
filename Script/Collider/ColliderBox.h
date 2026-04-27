#pragma once
#include "ColliderBase.h"
#include "../Common/Vector2.h"

class ColliderBox : public ColliderBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">衝突判定タグ</param>
	/// <param name="followPos">追従対象の座標</param>
	/// <param name="boxSize">ボックスサイズ</param>
	/// <param name="radAngle">追従対象の角度</param>
	ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, const Vector2& boxSize, float& radAngle);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderBox() override;

	/// <summary>
	/// 自身の複製を生成
	/// </summary>
	/// <returns>複製したインスタンス</returns>
	std::shared_ptr<ColliderBase> Clone() const override;

	/// <summary>
	/// ボックスサイズの設定
	/// </summary>
	/// <param name="topPos">ボックスサイズ</param>
	void SetBoxSize(const Vector2& topPos) { boxSize_ = topPos; }

	/// <summary>
	/// ボックスサイズを返す
	/// </summary>
	/// <returns>ボックスサイズ</returns>
	const Vector2& GetBoxSize() const { return boxSize_; }

	/// <summary>
	/// ハーフサイズを返す
	/// </summary>
	/// <returns></returns>
	const Vector2& GetBoxHalfSize()const { return boxHalfSize_; }

	/// <summary>
	/// 右上座標の相対位置を返す
	/// </summary>
	/// <returns>右上座標の相対位置</returns>
	const Vector2& GetLocalTopPos() const;

	/// <summary>
	/// 左下座標の相対位置を返す
	/// </summary>
	/// <returns>左下座標の相対位置</returns>
	const Vector2& GetLocalBottomPos() const;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

	/// @brief OBB(回転矩形)のローカル軸の取得
	/// @param angle 向いている角度
	/// @return 矩形が向いている右方向
	const Vector2F& GetAxisX(void)const;

	/// @brief OBB(回転矩形)のローカル軸の取得
	/// @param angle 向いている角度
	/// @return 矩形が向いている上方向
	const Vector2F& GetAxisY(void)const;

	/// <summary>
	/// 軸上で相手と重なっているかを返す
	/// </summary>
	/// <param name="opponent">相手のボックスコライダ</param>
	/// <returns></returns>重なっている
	bool OverlapOnAxis(const std::weak_ptr<ColliderBox>& opponent,const Vector2F& axis);



private:

	// ボックスサイズ
	Vector2 boxSize_;

	// ハーフサイズ
	Vector2 boxHalfSize_;

	//角度(デグリー)
	const float& radAngle_;
};