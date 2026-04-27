#pragma once
#include "../ActorBase.h"

class GimmickBase :public ActorBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータを指定</param>
	/// <param name="componentNameList">付与する機能</param>
	GimmickBase(Parameter* parameter, const std::vector<std::string>& componentNameList = {});

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickBase()override;

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
	/// 描画
	/// </summary>
	/// <param name=""></param>
	void Draw(void)override;

	/// <summary>
	/// デバッグ表示
	/// </summary>
	/// <param name=""></param>
	void DebugDraw(void)override;
private:



};