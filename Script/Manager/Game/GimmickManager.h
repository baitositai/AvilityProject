#pragma once
#include <vector>
#include "../Common/Vector2F.h"
#include "../../Template/Singleton.h"
#include "../../Object/Gimmick/GimmickBase.h"

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

	/// <summary>
	/// 指定したギミックのパラメータを返す
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>パラメータ</returns>
	std::unique_ptr<ParameterGimmick> GetGimmickParameter(const GimmickBase::TYPE type) const;


private:

	// ギミックリスト
	std::vector<std::unique_ptr<GimmickBase>> gimmickList_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<GimmickBase::TYPE, std::unique_ptr<ParameterGimmick>> templateParameterMap_;
	
	// パラメータ関係の初期化
	void InitParameter();

	// コンストラクタ
	GimmickManager();

	// デストラクタ
	~GimmickManager();
};