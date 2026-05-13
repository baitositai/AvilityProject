#pragma once
#include "../ComponentBase.h"

class Player;
class StageManager;
class SceneManager;
class InputManager;

// アビリティ用スロット
enum class ABILITY_SLOT
{
	FIRST = 0,
	SECOND = 1,
	THIRD = 2,
	MAX
};

class ComponentAvilityBase : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityBase(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentAvilityBase() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 取り外し時の処理
	/// </summary>
	virtual void Remove();

	/// <summary>
	/// アビリティスロットの種類を返す
	/// </summary>
	/// <returns>アビリティスロットの種類</returns>
	ABILITY_SLOT GetAbilitySlot() const { return abilitySlot_; }

protected:

	// 所有者
	Player& owner_;

	//ステージマネージャ
	StageManager& stageManager_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 入力管理クラスの参照
	InputManager& inputManager_;	
	
	// アビリティスロット
	ABILITY_SLOT abilitySlot_;
};