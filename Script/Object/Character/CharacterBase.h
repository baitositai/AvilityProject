#pragma once
#include "../ActorBase.h"

struct CharacterParameterBase
{
	int hp = -1;				// 体力
	int attackPower = -1;		// 攻撃力
	float moveSpeed = 0.0f;		// 移動速度
};

class CharacterBase : public ActorBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharacterBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CharacterBase();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() override;

protected:

private:

};

