#pragma once
#include "../ActorBase.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"

class ComponentSpriteAnimation;

class CharacterBase : public ActorBase
{
public:
	
	// キャラクターの共通パラメータ
	struct Parameter
	{
		int hp = -1;				// 体力
		int attackPower = -1;		// 攻撃力
		float moveSpeed = 0.0f;		// 移動速度
		Vector2F pos = {};			// 位置
	};
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	CharacterBase(const Parameter& parameter);

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

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const Parameter& GetParameter() const { return parameter_; }

protected:

	// キャラクターのパラメータ
	Parameter parameter_;

private:

	// スプライトアニメーションコンポーネント
	std::unique_ptr<ComponentSpriteAnimation> spriteAnimation_;

};

