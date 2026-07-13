#pragma once
#include "../Common/Vector2.h"

class ResourceManager;

class UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UiBase();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 削除処理
	/// </summary>
	virtual void Delete();
	
	/// <summary>
	/// 座標位置の設定
	/// </summary>
	/// <param name="pos"></param>
	virtual void SetPos(const Vector2& pos) { pos_ = pos; }

	/// <summary>
	/// 活動状態の設定
	/// </summary>
	/// <param name="isActive">活動状態</param>
	void SetIsActive(const bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// 削除判定を返す
	/// </summary>
	/// <returns>削除判定</returns>
	const bool IsDelete() const { return isDelete_; }

	/// <summary>
	/// 活動状態を返す
	/// </summary>
	const bool IsActive() const { return isActive_; }

protected:

	// 削除判定
	bool isDelete_;

	// 活動判定
	bool isActive_;

	// 拡大率
	float scale_;

	// 角度
	float angle_;

	// リソース
	int handle_;

	// 座標
	Vector2 pos_;

	// リソース管理
	ResourceManager& resourceManager_;
};