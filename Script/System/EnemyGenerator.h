#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "../Common/Vector2.h"
#include "../Manager/Game/EnemyTypes.h"

class EnemyBase;
class EnemyClone;
class EnemySlime;
class EnemyMushroom;
class EnemySnake;
class EnemyHat;
class EnemySamurai;

class ParameterEnemy;
enum class HABITAT_TYPE;

class EnemyGenerator
{
public:	
	
	// 敵の各種類に定義する値
	struct SpawnConfig
	{
		float spawnRate;
		HABITAT_TYPE habitatType;
	};

	// ステージ内の敵を生成する際のパラメータ
	struct Parameter
	{
		int createEnemyCountMin;		// 一つの座標で生成する敵の最小数
		int createEnemyCountMax;		// 一つの座標で生成する敵の最大数
		Vector2F createRange;			// 生成範囲
		std::unordered_map<EnemyTypes::TYPE, SpawnConfig> spawnConfigMap;	// 各敵毎の生成に関するマップ
	};


	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyGenerator();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyGenerator();

	/// <summary>
	/// パラメータ情報を初期化
	/// </summary>
	void InitParameter();

	/// <summary>
	/// 敵を管理するマップを生成
	/// </summary>
	/// <param name="CreatePositionsList">生成位置リスト</param>
	/// <param name="">敵の生成率管理マップ</param>
	/// <returns>敵を管理するマップ</returns>
	std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> CreateEnemyMap(const std::vector<Vector2F>& createPositionsList, const std::unordered_map<EnemyTypes::TYPE, SpawnConfig> spawnConfigMap);

	/// <summary>
	/// 敵の生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>敵のインスタンス</returns>
	std::unique_ptr<EnemyBase> CreateEnemy(const EnemyTypes::TYPE type);

private:

	// 敵の生成マップ
	std::unordered_map<EnemyTypes::TYPE, std::function<std::unique_ptr<EnemyBase>()>> createEnemyMap_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<EnemyTypes::TYPE, std::unique_ptr<ParameterEnemy>> templateParameterMap_;

	// 確立に基づいて敵の種類を決定する
	EnemyTypes::TYPE LotteryEnemyType(const std::unordered_map<EnemyTypes::TYPE, SpawnConfig>& spawnTable);

	// 各種敵の生成処理
	std::unique_ptr<EnemyClone> CreateEnemyClone();
	std::unique_ptr<EnemySlime> CreateEnemySlime();
	std::unique_ptr<EnemyMushroom> CreateEnemyMushroom();
	std::unique_ptr<EnemySnake> CreateEnemySnake();
	std::unique_ptr<EnemyHat> CreateEnemyHat();
	std::unique_ptr<EnemySamurai> CreateEnemySamurai();
};