#pragma once
#include "ComponentBase.h"

class CharacterBase;
class SceneManager;

class ComponentInvincible : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentInvincible(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentInvincible() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 所有者
	CharacterBase& owner_;

	// シーン管理クラス
	SceneManager& sceneManager_;
};