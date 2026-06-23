#pragma once
#include "../ComponentBase.h"
#include "AvilityTypes.h"

class Player;
class ParameterPlayer;
class StageManager;
class SceneManager;
class InputManager;
class SpriteEffectManager;
class CollisionManager;

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
	/// 生成処理
	/// </summary>
	virtual void Create();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 取り外し時の処理
	/// </summary>
	virtual void Remove() override;

	/// <summary>
	/// 種類を返す
	/// </summary>
	/// <returns>種類</returns>
	const AvilityTypes::TYPE GetType() const { return type_; }

	/// <summary>
	/// リソース用アビリティ番号を設定
	/// </summary>
	/// <param name="index"></param>
	void SetAvilityResourceIndex(const int index) { avilityResourceIndex_ = index; }

	/// <summary>
	/// リソース用アビリティ番号を返す
	/// </summary>
	/// <returns>リソース用アビリティ番号</returns>
	const int GetAvilityResourceIndex() const { return avilityResourceIndex_; }

protected:

	// 所有者
	Player& owner_;

	// パラメーター
	ParameterPlayer& parameter_;

	//ステージマネージャ
	StageManager& stageManager_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 入力管理クラスの参照
	InputManager& inputManager_;	

	// エフェクト管理クラスの参照
	SpriteEffectManager& effectManager_;

	// 衝突判定管理クラスの参照
	CollisionManager& collisionManager_;

	// 種類
	AvilityTypes::TYPE type_;

	// アビリティリソース番号
	int avilityResourceIndex_;
};