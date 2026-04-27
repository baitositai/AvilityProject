#pragma once
#include "../ActorBase.h"

class GimmickBase :public ActorBase
{
public:

	enum class TYPE
	{
		AVILITY_BOX,
	};

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

	/// <summary>
	/// ギミック種類の取得
	/// </summary>
	/// <param name=""></param>
	/// <returns>ギミック種類</returns>
	const TYPE GetGimmickType(void)const { return gimmickType_; }
protected:
	//ギミックの種類
	TYPE gimmickType_;
private:


};