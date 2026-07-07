#pragma once
#include <memory>
#include <vector>
#include <random>
#include <unordered_map>
#include "../Common/Vector2.h"
#include "../Manager/Game/EnemyTypes.h"

// 雑魚敵
class EnemyBase;
class EnemyClone;
class EnemySlime;
class EnemyMushroom;
class EnemySnake;
class EnemyHat;
class EnemySamurai;

// ボス
class EnemyMaid;
class EnemyPanda;
class EnemyGaiaGolem;

class ParameterEnemy;
enum class HABITAT_TYPE;

class EnemyGenerator
{
public:

	struct Parameter
	{
		int createCountMin;		// 最小生成数
		int createCountMax;		// 最大生成数
		Vector2F createRange;	// 生成範囲
		std::vector<Vector2F> createPositionsList;			// 生成位置のリスト
		std::vector<EnemyTypes::TYPE> createEnemyTypeList;	// 生成する敵の種類リスト
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
	/// <param name="parameter">パラメータ情報</param>
	std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> CreateEnemyMap(const Parameter& parameter);

	/// <summary>
	/// 敵の生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>敵のインスタンス</returns>
	std::unique_ptr<EnemyBase> CreateEnemy(const EnemyTypes::TYPE type);

private:

	// 乱数生成エンジン
	std::mt19937 randomCountEngine_;

	// 敵の生成マップ
	std::unordered_map<EnemyTypes::TYPE, std::function<std::unique_ptr<EnemyBase>()>> createEnemyMap_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<EnemyTypes::TYPE, std::unique_ptr<ParameterEnemy>> templateParameterMap_;

	// 敵の生成確率から抽選して種類を返す
	EnemyTypes::TYPE LotteryEnemyType(const std::unordered_map<EnemyTypes::TYPE, float>& spawnTable);

	// 各種敵の生成処理
	std::unique_ptr<EnemyClone> CreateEnemyClone();
	std::unique_ptr<EnemySlime> CreateEnemySlime();
	std::unique_ptr<EnemyMushroom> CreateEnemyMushroom();
	std::unique_ptr<EnemySnake> CreateEnemySnake();
	std::unique_ptr<EnemyHat> CreateEnemyHat();
	std::unique_ptr<EnemySamurai> CreateEnemySamurai();

	std::unique_ptr<EnemyMaid> CreateEnemyMaid();
	std::unique_ptr<EnemyPanda> CreateEnemyPanda();
	std::unique_ptr<EnemyGaiaGolem> CreateEnemyGaiaGolem();
};