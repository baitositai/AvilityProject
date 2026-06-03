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

class EnemyGenerator
{
public:
	
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
	/// <returns>敵を管理するマップ</returns>
	std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> CreateEnemyMap(const std::vector<Vector2F>& CreatePositionsList);

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

	// 各種敵の生成処理
	std::unique_ptr<EnemyClone> CreateEnemyClone();
	std::unique_ptr<EnemySlime> CreateEnemySlime();
	std::unique_ptr<EnemyMushroom> CreateEnemyMushroom();
	std::unique_ptr<EnemySnake> CreateEnemySnake();
	std::unique_ptr<EnemyHat> CreateEnemyHat();
	std::unique_ptr<EnemySamurai> CreateEnemySamurai();
};