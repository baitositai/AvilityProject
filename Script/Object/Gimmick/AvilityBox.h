#pragma once
#include "../Common/Vector2.h"
#include "GimmickBase.h"

class OnHitAvilityBox;
class CharacterBase;

class AvilityBox :public GimmickBase
{
public:

	struct Parameter :public ActorBase::Parameter
	{
		Vector2 hitBoxSize;		//サイズ
		Vector2 hitLocalPos;	//ボックスの当たり判定のローカル座標
		Vector2F placePos;		//設置時のプレイヤーとのローカル座標
		float blastTime;		//爆発するまでの時間
		int boxNum;				//何個目のボックスか

		bool isGround = false;				// 地面判定
		bool isFall = false;				// 落下判定
	};

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
	/// <param name="componentNameList">付与コンポーネント</param>
	AvilityBox(const Parameter& parameter, CharacterBase& _chara, const std::vector<std::string>& componentNameList = {});

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AvilityBox();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name=""></param>
	void Init(void)override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name=""></param>
	void Update(void)override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name=""></param>
	void Draw(void)override;

	/// <summary>
	/// デバッグ表示
	/// </summary>
	/// <param name=""></param>
	void DebugDraw(void)override;

	/// <summary>
	/// パラメーターの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Vector2& GetHitBoxSize(void)const { return parameter_.hitBoxSize; }

	/// <summary>
	/// ボックスの重みを取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const float GetWeight(void)const { return parameter_.weight; }

	/// <summary>
	/// プレイヤーが押している状態のセット
	/// </summary>
	/// <param name=""></param>
	void SetPlayerPush(void) { isPushPlayer_ = true; }

	/// <summary>
	/// プレイヤー押し出し状態の取得
	/// </summary>
	/// <param name=""></param>
	/// <returns>true：プレイヤー押し出し中　false:押し出していない</returns>
	const bool& GetIsPlayerPush(void)const { return isPushPlayer_; }

	/// <summary>
	/// 地面判定
	/// </summary>
	/// <param name="_isGround"></param>
	void isGround_(const bool _isGround) { parameter_.isGround = _isGround; }


	const int GetBoxNum(void)const { return parameter_.boxNum; }


	void AddHitInfo(const HitInfo& _hitInfo);

	const bool GetIsHitWall(void)const { return isHitWall_; }

	void SetIsHitWall(const bool _isHit) { isHitWall_ = _isHit; }

private:

	//当たっている箱の情報
	std::vector<HitInfo> hitInfo_;

	// パラメータ情報
	Parameter parameter_;

	//キャラクター情報
	CharacterBase& character_;

	//爆発までのカウント
	float blastWaitCnt_;

	//プレイヤー押し出しの判別
	bool isPushPlayer_;

	//壁に当たっているか
	bool isHitWall_;

	//最終的な押し出し処理
	void PushResult(void);
};