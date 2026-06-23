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
	/// <param name="type">種類</param>
	/// <param name="pos">座標</param>
	/// <param name="isMove">移動判定</param>
	/// <param name="moveDir">移動方向</param>
	void Add(const GimmickTypes::TYPE type, const Vector2F& pos);

	/// <summary>
	/// ボス部屋ドアの生成
	/// </summary>
	/// <param name="pos"></param>
	void CreateBossDoor(const Vector2F pos);

	/// <summary>
	/// ターゲットの生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="isMove">移動判定</param>
	void CreateTarget(const Vector2F pos, const Vector2F& moveDir = {});

	/// <summary>
	/// 吹き出しの生成
	/// </summary>
	/// <param name="followPos">追従座標</param>
	/// <param name="resourceName">リソース名</param>
	/// <param name="displayTime">表示時間</param>
	void CreateSpeechBubble(const Vector2F* followPos, const std::string& resourceName, const float displayTime = -1.0f);

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