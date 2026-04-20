#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:

	struct Parameter : public CharacterBase::Parameter
	{
		Vector2 hitBoxSize_;
		Vector2 hitLocalPos_;
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="componentNameList">コンポーネント生成用名前リスト</param>
	Player(const Parameter& parameter, const std::vector<std::string> componentNameList);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 衝突する範囲を返す
	/// </summary>
	/// <returns>衝突する範囲</returns>
	const Vector2& GetHitBoxSize() const { return parameter_.hitBoxSize_; }

private:

	// パラメータ情報
	Parameter parameter_;
};