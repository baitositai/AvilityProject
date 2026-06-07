#pragma once
#include "../Component/State/ComponentCharacterStateBase.h"

class CharacterBase;
class ParameterCharacter;
class ColliderCircle;

class ComponentStateAttackDefault : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateAttackDefault(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateAttackDefault() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 取り外し処理
	/// </summary>
	void Remove() override;

private:

	// 攻撃開始フレーム
	const int ATTACK_START_FRAME;

	// 通常攻撃の相対位置
	const float ATTACK_DISTANCE;

	// 所有者
	CharacterBase& owner_;

	// パラメータ
	ParameterCharacter& parameter_;

	// 攻撃位置
	Vector2F attackPos_;

	// 攻撃開始
	bool isAttack_;

	std::shared_ptr<ColliderCircle> collider_;
};