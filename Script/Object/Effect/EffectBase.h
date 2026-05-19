#pragma once
#include "../ActorBase.h"

class EffectBase : public ActorBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメーター</param>
	/// <param name="componentNameList">コンポーネントリスト</param>
	/// <param name="animation"></param>
	EffectBase(Parameter* parameter = {}, const std::vector<std::string>& componentNameList = {}, std::unique_ptr<Animation> animation = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EffectBase() override;

private:

};