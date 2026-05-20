#pragma once
#include "../Common/Vector2.h"
#include "../../Parameter/Gimmick/ParameterAvilityBox.h"
#include "GimmickBase.h"

class OnHitAvilityBox;
class CharacterBase;

class AvilityBox :public GimmickBase
{
public:

	struct HitInfo
	{
		//優先度
		int priority = -1;

		//めり込み量
		float overlapX = 0.0f;
		float overlapY = 0.0f;

		//現在押し出されている方向(押し出したい方向ではない)
		int signX = 0;
		int signY = 0;

		//移動量
		Vector2F moveAmount = { 0.0f,0.0f };

		//誰が押しているか
		bool selfPlayerPush = false;			//自身がプレイヤーに押されている
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <param name="owner">所有者</param>
	explicit AvilityBox(std::unique_ptr<ParameterAvilityBox> paramter, CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AvilityBox() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Draw()override;

	/// <summary>
	/// デバッグ表示
	/// </summary>
	void DebugDraw()override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterAvilityBox& GetParameter() { return *parameterAvilityBox_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterAvilityBox& GetParameter() const { return *parameterAvilityBox_; }

	/// <summary>
	/// プレイヤーが押している状態のセット
	/// </summary>
	void SetPlayerPush() { isPushPlayer_ = true; }

	/// <summary>
	/// プレイヤー押し出し状態の取得
	/// </summary>
	/// <returns>true：プレイヤー押し出し中　false:押し出していない</returns>
	const bool& GetIsPlayerPush()const { return isPushPlayer_; }

	/// <summary>
	/// 衝突情報の格納
	/// </summary>
	/// <param name="hitInfo">衝突情報</param>
	void AddHitInfo(const HitInfo& hitInfo);

	/// <summary>
	/// 壁に衝突しているか返す
	/// </summary>
	/// <returns></returns>
	const bool GetIsHitWall()const { return isHitWall_; }

	/// <summary>
	/// 壁との衝突設定
	/// </summary>
	/// <param name="isHit">衝突判定</param>
	void SetIsHitWall(const bool isHit) { isHitWall_ = isHit; }

private:

	//当たっている箱の情報
	std::vector<HitInfo> hitInfo_;

	// パラメータ情報
	ParameterAvilityBox* parameterAvilityBox_;

	// 管理者
	CharacterBase& owner_;

	//爆発までのカウント
	float blastWaitCnt_;

	//プレイヤー押し出しの判別
	bool isPushPlayer_;

	//壁に当たっているか
	bool isHitWall_;

	//最終的な押し出し処理
	void PushResult();
};