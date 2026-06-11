#pragma once
#include "EventBase.h"
#include "../../Parameter/Event/ParameterEventTargetDestroy.h"

class EventTargetDestroy : public EventBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	EventTargetDestroy(std::unique_ptr<ParameterEventTargetDestroy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EventTargetDestroy() override;
};

