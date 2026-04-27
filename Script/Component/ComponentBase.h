#pragma once

class ActorBase;

class ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentBase(ActorBase* owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentBase();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 活動状態を設定する
	/// </summary>
	/// <param name="isActive">活動状態</param>
	void SetActive(const bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// 活動状態を返す
	/// </summary>
	/// <returns>活動状態</returns>
	const bool IsActive() const { return isActive_; }

protected:

	ActorBase* owner_;

	// 活動状態
	bool isActive_;
};

