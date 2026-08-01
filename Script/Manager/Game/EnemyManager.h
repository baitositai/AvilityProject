#pragma once
#include <vector>
#include <unordered_map>
#include "../../Template/Singleton.h"
#include "EnemyTypes.h"

class EnemyBase;
class EnemyGenerator;

class EnemyManager : public Singleton<EnemyManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<EnemyManager>;

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
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="createPositionList">生成位置を格納したリスト</param>
	void Generator(const std::vector<Vector2F>& createPositionList);

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="pos">生成位置</param>
	void Create(const EnemyTypes::TYPE type, const Vector2F& pos);

	/// <summary>
	/// ボス生成処理
	/// </summary>
	/// <param name="type"></param>
	/// <param name="pos"></param>
	void CreateBoss(const EnemyTypes::TYPE type, const Vector2F& pos);
	
	/// <summary>
	/// イベント用の敵生成処理
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="pos">生成位置</param>
	void CreateEventEnemy(const EnemyTypes::TYPE type, const Vector2F& pos);

	/// <summary>
	/// チュートリアル用の敵を生成
	/// </summary>
	/// <param name="pos">生成位置</param>
	void CreateTutorialEnemy(const Vector2F& pos);

	/// <summary>
	/// イベントで発生した敵を全削除
	/// </summary>
	void DestroyEventEnemy();

	/// <summary>
	/// 削除
	/// </summary>
	void Clear();	

	/// <summary>
	/// 停止設定
	/// </summary>
	/// <param name="isStop"></param>
	void SetIsStop(const bool isStop) { isStop_ = isStop; }

	/// <summary>
	/// ボスの指定
	/// </summary>
	/// <param name="type">ボス種類</param>
	void SetBossEnemyType(const EnemyTypes::TYPE type) { createBossEnemyType_ = type; }

	/// <summary>
	/// サンドバッグとなる敵を生成
	/// </summary>
	/// <param name="pos">座標</param>
	void CreateSandBagEnemy(const Vector2F& pos);

	/// <summary>
	/// ボスを撃破できたか
	/// </summary>
	/// <returns>trueは撃破、falseは生存</returns>
	const bool IsBossDestroy(const EnemyTypes::TYPE type) const;

	/// <summary>
	/// イベント用の敵がいない返す
	/// </summary>
	/// <returns>trueの場合空</returns>
	const bool IsEmptyEventEnemies();

	/// <summary>
	/// ボスの種類を返す
	/// </summary>
	/// <returns>ボス種類</returns>
	const EnemyTypes::TYPE GetBossEnemyType() const { return createBossEnemyType_; }

private:

	// 更新の停止
	bool isStop_;

	// 生成するボスのタイプ
	EnemyTypes::TYPE createBossEnemyType_;

	// 敵の生成に関するジェネレーター
	std::unique_ptr<EnemyGenerator> enemyGenerator_;

	// 敵を管理するマップ
	std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> enemiesMap_;

	// イベントで生成した敵を管理するリスト
	std::vector<EnemyBase*> eventEnemyList_;

	// コンストラクタ
	EnemyManager();

	// デストラクタ
	~EnemyManager();
};
