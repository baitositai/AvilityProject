#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2F.h"

class EffectBase;
class ActorBase;

class SpriteEffectManager : public Singleton<SpriteEffectManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<SpriteEffectManager>;

public:

	// 生成情報
	struct CreateParameter
	{
		Vector2F pos = {};
		float scale = 1.0f;
		float angle = 0.0f;
		float animationSpeed = 0.0f;
		float animationNum = -1;
		bool direction = false;
		bool isLoop = false;
		std::string resourceKey = "";
		ActorBase* target = nullptr;
	};

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
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 追加処理
	/// </summary>
	/// <param name="effect">エフェクト</param>
	void Add(std::unique_ptr<EffectBase> effect);

	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="createParameter">パラメータ情報</param>
	/// <returns>生成ID</returns>
	int Create(const CreateParameter createParameter);

	/// <summary>
	/// 削除処理
	/// </summary>
	/// <param name="id">エフェクト番号</param>
	void Delete(const int id);

	/// <summary>
	/// 中身を空にする
	/// </summary>
	void Clear();

	/// <summary>
	/// 削除処理
	/// </summary>
	void Sweep();

private:

	// エフェクトID
	int nextId_;

	// エフェクトリスト
	std::vector<std::unique_ptr<EffectBase>> effectList_;

	// コンストラクタ
	SpriteEffectManager();

	// デストラクタ
	~SpriteEffectManager();
};