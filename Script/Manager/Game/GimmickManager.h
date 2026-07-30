#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "../../Template/Singleton.h"
#include "../../Common/Vector2F.h"
#include "GimmickTypes.h"

class GimmickBase;
class GimmickGenerator;

class GimmickManager : public Singleton<GimmickManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<GimmickManager>;

public:

	struct CreateParameter
	{
		GimmickTypes::TYPE type = GimmickTypes::TYPE::MAX;
		Vector2F pos = {};
		Vector2F moveDir = {};
		int attackPower = -1;
		int hp = -1;
	};

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
	/// 生成処理
	/// </summary>
	/// <param name="parameter">生成パラメータ</param>
	void Create(const CreateParameter& parameter);

	/// <summary>
	/// ボス部屋ドアの生成
	/// </summary>
	/// <param name="pos">座標位置</param>
	void CreateBossDoor(const Vector2F& pos);

	/// <summary>
	/// ボス部屋ドアの生成
	/// </summary>
	/// <param name="pos">座標位置</param>
	void CreateGroundRock(const CreateParameter& _parameter,const float _horizontalSpd);

	/// <summary>
	/// ターゲットをすべて消す
	/// </summary>
	void AllDeleteTarget();

	/// <summary>
	/// 全てのターゲットを破壊することができたか
	/// </summary>
	/// <returns>空の場合true</returns>
	const bool IsDestrolyAllTarget() const;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// ショップ位置を返す
	/// </summary>
	/// <returns>ショップ位置</returns>
	const Vector2F GetShopPos() const;

	/// <summary>
	/// チュートリアル用の電車の生成
	/// </summary>
	void CreateTutorialTrain();

	/// <summary>
	/// 電車を消す
	/// </summary>
	void DeleteTrain();

private:

	// ギミック生成
	std::unique_ptr<GimmickGenerator> gimmickGenerator_;

	// ギミック管理マップ
	std::unordered_map<GimmickTypes::TYPE, std::vector<std::unique_ptr<GimmickBase>>> gimmickListMap_;

	// コンストラクタ
	GimmickManager();

	// デストラクタ
	~GimmickManager();
};