#pragma once
#include "../Common/Vector2.h"
#include "./GimmickBase.h"

class AvilityBox :public GimmickBase
{
public:

	struct Parameter :public ActorBase::Parameter
	{
		Vector2 hitBoxSize;
		Vector2 hitLocalPos;
		float blastTime;
	};

	enum class STATE
	{

	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <param name="componentNameList">付与コンポーネント</param>
	AvilityBox(const Parameter& parameter, const std::vector<std::string>& componentNameList = {});

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

private:

	// パラメータ情報
	Parameter parameter_;

	//爆発までのカウント
	float blastWaitCnt_;
};