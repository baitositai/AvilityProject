#pragma once
#include <vector>
#include "../Common/Vector2F.h"
#include "../../Template/Singleton.h"

class GimmickGenerator;
class GimmickBase;

class GimmickManager : public Singleton<GimmickManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<GimmickManager>;

public:

	/// <summary>
	/// 初期化処理
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
	/// 削除処理
	/// </summary>
	void Sweep();

	/// <summary>
	/// クリア処理
	/// </summary>
	void Clear();

	/// <summary>
	/// 追加処理
	/// </summary>
	/// <param name="gimmick">ギミック</param>
	void Add(std::unique_ptr<GimmickBase> gimmick);

	/// <summary>
	/// ボス部屋の設定
	/// </summary>
	/// <param name="pos"></param>
	void SetBossDoor(const Vector2F pos);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// ギミックリスト
	std::vector<std::unique_ptr<GimmickBase>> gimmickList_;

	// ギミック生成
	std::unique_ptr<GimmickGenerator> gimmickGenerator_;

	// コンストラクタ
	GimmickManager();

	// デストラクタ
	~GimmickManager();
};