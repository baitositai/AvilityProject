#pragma once
#include "CharacterBase.h"

struct PlayerParameter : public CharacterParameterBase
{
	CharacterParameterBase base;	// 基本パラメータ
};

class Player : public CharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	Player(const PlayerParameter& parameter);

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
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	// パラメータ
	PlayerParameter parameter_;

};

