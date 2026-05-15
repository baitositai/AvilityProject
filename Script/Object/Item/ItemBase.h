#pragma once
#include "../ActorBase.h"

class ItemBase : public ActorBase
{
public:

	struct Parameter : public ActorBase::Parameter
	{
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="componentNameList">コンポーネントリスト</param>
	/// <param name="animation">アニメーション情報</param>
	ItemBase(Parameter* parameter, const std::vector<std::string>& componentNameList = {}, std::unique_ptr<Animation> animation = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ItemBase() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	virtual void DebugDraw() override;

private:

	// アイテムのパラメータ
	Parameter* itemParameterPtr_;

};