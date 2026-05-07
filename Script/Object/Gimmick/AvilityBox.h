#pragma once
#include "../Common/Vector2.h"
#include "GimmickBase.h"

class OnHitAvilityBox;

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
	};

	struct HitInfo
	{
		//優先度
		int priority;

		//めり込み量
		float overlapX = 0.0f;
		float overlapY = 0.0f;

		//押し出し方向
		int signX;
		int signY;

		//誰が押しているか
		bool selfPlayerPush = false;			//自身がプレイヤーに押されている
	};

	enum class STATE
	{

	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <param name="componentNameList">付与コンポーネント</param>
	AvilityBox(const Parameter& parameter, const Vector2F& _charaPos, const std::vector<std::string>& componentNameList = {});

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
	const bool GetIsPlayerPush(void)const { return isPushPlayer_; }


	const int GetBoxNum(void) { return parameter_.boxNum; }


	void AddHitInfo(const HitInfo& _hitInfo);

private:


	//当たっている箱の情報
	std::vector<HitInfo> hitInfo_;

	// パラメータ情報
	Parameter parameter_;

	//爆発までのカウント
	float blastWaitCnt_;

	//プレイヤー押し出しの判別
	bool isPushPlayer_;



	void PushResult(void);
};