#pragma once
#include <vector>
#include <unordered_map>
#include "../../Template/Singleton.h"

class EffectBase;

class SpriteEffectManager : public Singleton<SpriteEffectManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<SpriteEffectManager>;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 追加処理
	/// </summary>
	/// <param name="effect">エフェクト</param>
	void Add(std::unique_ptr<EffectBase> effect);

	/// <summary>
	/// 中身を空にする
	/// </summary>
	void Clear();

	/// <summary>
	/// 削除処理
	/// </summary>
	void Sweep();

private:

	// エフェクトリスト
	std::vector<std::unique_ptr<EffectBase>> effectList_;

	// コンストラクタ
	SpriteEffectManager();

	// デストラクタ
	~SpriteEffectManager();
};