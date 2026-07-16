#pragma once
#include "../UiBase.h"

class EventBase;

class UiEventBase : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiEventBase(const EventBase& event);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UiEventBase() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

protected:

	const EventBase& eventBase_;
};

