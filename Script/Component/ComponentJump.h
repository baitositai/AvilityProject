#pragma once
#include "ComponentBase.h"]

class CharacterBase;
class SceneManager;
class Animation;

class ComponentJump : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentJump(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentJump() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 所有者
	CharacterBase& owner_;

	// シーン管理クラス
	SceneManager& scnMng_;

	// アニメーション
	Animation& animation_;
};