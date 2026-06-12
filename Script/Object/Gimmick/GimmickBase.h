#pragma once
#include "../ActorBase.h"
#include "../../Parameter/Gimmick/ParameterGimmick.h"

class GimmickBase :public ActorBase
{
public:

	// 種類
	enum class TYPE
	{
		AVILITY_BOX,
		DOOR,
		TARGET,
		MAX,
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータを指定</param>
	explicit GimmickBase(std::unique_ptr<ParameterGimmick> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickBase()override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// デバッグ表示
	/// </summary>
	void DebugDraw()override;

	/// <summary>
	/// リソース取得
	/// </summary>
	void InitResource() override;

	/// <summary>
	/// ギミック種類の取得
	/// </summary>
	/// <returns>ギミック種類</returns>
	const TYPE GetGimmickType()const { return gimmickType_; }

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterGimmick& GetParameter() { return *parameterGimmick_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterGimmick& GetParameter() const { return *parameterGimmick_; }

protected:
	
	//ギミックの種類
	TYPE gimmickType_;

	// 型変換用のパラメータを返す関数
	ParameterGimmick* GetParameterGimmickPtr() { return parameterGimmick_; }

private:

	// パラメータ情報
	ParameterGimmick* parameterGimmick_;

};