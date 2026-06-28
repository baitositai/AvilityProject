#include <algorithm>
#include "../../Collider/ColliderBase.h"
#include "../../Collider/ColliderBox.h"
#include "../../Collider/ColliderCircle.h"
#include "../../Collider/ColliderLine.h"
#include "../../Collider/ColliderFan.h"
#include "../../Collider/ColliderArray.h"
#include "../../Object/ActorBase.h"
#include "../../Utility/UtilityCollision.h"
#include "CollisionManager.h"

void CollisionManager::Init()
{
	// 衝突判定の組み合わせを初期化
	InitTagMatrix();
	InitColliderMatrix();
}

void CollisionManager::Update()
{
	// 配列サイズ
	const int size = static_cast<int>(colliders_.size());

	//コリジョンタグの順番に並べ、処理順を整える
	std::sort(colliders_.begin(), colliders_.end(),
		[this](const std::weak_ptr<ColliderBase>col1, const std::weak_ptr<ColliderBase>col2)
		{
			return col1.lock()->GetTag() < col2.lock()->GetTag();
		});

	for (int i = 0; i < size - 1; i++)
	{
		//衝突判定の初期化
		colliders_[i]->SetIsHit(false);

		// スキップ判定
		if (colliders_[i]->IsSkip())
		{
			// 次へ
			continue;
		}

		for (int j = i + 1; j < size; j++)
		{
			//衝突判定の初期化
			colliders_[j]->SetIsHit(false);

			// スキップ判定
			if (colliders_[j]->IsSkip())
			{
				// 次へ
				continue;
			}

		/*	auto& collider = colliders_[i];
			auto& collider2 = colliders_[j];*/

			// 各コライダーからタグを取得
			const auto& tag1 = colliders_[i]->GetTag();
			const auto& tag2 = colliders_[j]->GetTag();
			
			//if(tag1 == CollisionTags::TAG::TARGET && tag2 == CollisionTags::TAG::PLAYER_ATTACK_NORMAL ||
			//	tag1 == CollisionTags::TAG::PLAYER_ATTACK_NORMAL && tag2 == CollisionTags::TAG::TARGET)
			//{
			//	int a = 0;
			//}

			// 衝突判定が不要な組み合わせの場合
			if (!collTagMatrix_[static_cast<int>(tag1)][static_cast<int>(tag2)])
			{
				// 次へ
				continue;
			}

			// 各コライダーから種類を取得
			const auto& type1 = colliders_[i]->GetType();
			const auto& type2 = colliders_[j]->GetType();

			// 関数が登録されていない場合
			if (!collisionFunctionMatrix_[static_cast<int>(type1)][static_cast<int>(type2)])
			{
				// 次へ
				continue;
			}

			// 衝突判定関数を取得
			auto& collisionFunction = collisionFunctionMatrix_[static_cast<int>(type1)][static_cast<int>(type2)];

			// 衝突判定を実行
			if (collisionFunction(colliders_[i], colliders_[j]))
			{
				colliders_[i]->SetIsHit(true);
				colliders_[j]->SetIsHit(true);

				// お互いに相手のタグを設定
				colliders_[i]->SetPertnerTag(tag2);
				colliders_[j]->SetPertnerTag(tag1);

				// それぞれの当たった処理
				colliders_[i]->OnHit(colliders_[j]);
				colliders_[j]->OnHit(colliders_[i]);
			}
		}
	}
}

void CollisionManager::Add(std::shared_ptr<ColliderBase> collider)
{
	// 中身が空ではなく非登録済みの場合
	if (collider != nullptr && !collider->IsRegister())
	{
		// 登録
		collider->SetIsRegister(true);

		// コライダーの追加
		colliders_.push_back(collider);
	}
}

CollisionManager::CollisionResult CollisionManager::CheckStageCollision(const CollisionCheckParam& parameter)
{
	CollisionResult resultReturn;
	resultReturn.isHit = false;
	resultReturn.chipSize = 0.0f;
	resultReturn.chipIndex = 0;
	resultReturn.normal = Vector2F(0.0f, 0.0f);

	float sizeVal = parameter.isXAxis ? parameter.size.x : parameter.size.y;
	float otherSizeVal = parameter.isXAxis ? parameter.size.y : parameter.size.x;

	float margin = 0.45f;
	float offsets[] = { -margin, 0.0f, margin };

	for (float offset : offsets)
	{
		Vector2 checkPos = parameter.pos;

		if (parameter.isXAxis)
		{
			checkPos.x += (parameter.stepMove > 0.0f) ? sizeVal / 2.0f : -sizeVal / 2.0f;
			checkPos.y += otherSizeVal * offset;
		}
		else
		{
			checkPos.y += (parameter.stepMove > 0.0f) ? sizeVal / 2.0f : -sizeVal / 2.0f;
			checkPos.x += otherSizeVal * offset;
		}

		auto result = IsHitStage(checkPos);

		if (result.hit)
		{
			resultReturn.isHit = true;
			resultReturn.chipSize = parameter.isXAxis ? result.chipSize.x : result.chipSize.y;
			resultReturn.chipIndex = parameter.isXAxis ? result.hitChipIndex.x : result.hitChipIndex.y;

			// 法線の計算も共通化してしまう
			if (parameter.isXAxis)
			{
				resultReturn.normal.x = (parameter.stepMove > 0.0f) ? -1.0f : 1.0f;
			}
			else
			{
				resultReturn.normal.y = (parameter.stepMove > 0.0f) ? -1.0f : 1.0f;
			}
			break;
		}
	}

	return resultReturn;
}

ColliderArray::Result CollisionManager::IsHitStage(const Vector2& checkPos)
{
	ColliderArray::Result result{};

	// ステージのコライダーがない場合
	if (!stageCollider_) { return result; }

	// 判定
	result = stageCollider_->CheckHitMapChip(checkPos);

	// 判定結果を返す
	return result;
}

void CollisionManager::Clear()
{
	// 中身の削除
	colliders_.clear();

	int size = static_cast<int>(colliders_.size());
}

void CollisionManager::Sweep()
{
	// 終了したコライダを並び変える
	auto it = std::remove_if(colliders_.begin(), colliders_.end(),
		[](const std::weak_ptr<ColliderBase> collider)
		{
			return collider.lock()->IsDelete();
		});

	// 終了したコライダを削除する
	colliders_.erase(it, colliders_.end());
}

void CollisionManager::DebugDraw()
{
	for (auto& coll : colliders_)
	{
		if (coll->IsHit() || coll->IsDelete()) continue;
		coll->DebugDraw();
	}
}

void CollisionManager::InitTagMatrix()
{
	// サイズの定義
	collTagMatrix_.resize(CollisionTags::TAG_COUNT, std::vector<bool>(CollisionTags::TAG_COUNT, false));

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::STAGE)] = true;						// プレイヤーとステージ
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::STAGE)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	//collTagMatrix_[static_cast<int>(CollisionTags::TAG::AVILITY_BOX)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;					// アビリティ設置ボックスとプレイヤー
	//collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::AVILITY_BOX)] = true;

	//collTagMatrix_[static_cast<int>(CollisionTags::TAG::AVILITY_BOX)][static_cast<int>(CollisionTags::TAG::STAGE)] = true;					// アビリティ設置ボックスとステージ
	//collTagMatrix_[static_cast<int>(CollisionTags::TAG::STAGE)][static_cast<int>(CollisionTags::TAG::AVILITY_BOX)] = true;

	//collTagMatrix_[static_cast<int>(CollisionTags::TAG::AVILITY_BOX)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;			// アビリティ設置ボックスと敵
	//collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::AVILITY_BOX)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::STAGE)] = true;					// 敵とステージ
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::STAGE)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)] = true;	// 敵とプレイヤーの通常攻撃
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;					// プレイヤーと敵
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	//collTagMatrix_[static_cast<int>(CollisionTags::TAG::AVILITY_BOX)][static_cast<int>(CollisionTags::TAG::AVILITY_BOX)] = true;			//アビリティ設置ボックス同士

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;	// プレイヤースタンプと敵
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;	// プレイヤーショットと敵
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::AIRSLASH)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;				// エアースラッシュと敵
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::AIRSLASH)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;			// テレポートと敵
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::DOOR)] = true;						// プレイヤーとドア
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::DOOR)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;			// 敵同士
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)][static_cast<int>(CollisionTags::TAG::ENEMY_CLONE)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::ENEMY_VIEW)] = true;					// プレイヤー敵の視界
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_VIEW)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::ENEMY_ATTACK_NORMAL)] = true;			// プレイヤー敵の攻撃
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY_ATTACK_NORMAL)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::CHANGE_NEXT_AREA)] = true;			// プレイヤー次遷移エリア
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::CHANGE_NEXT_AREA)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)][static_cast<int>(CollisionTags::TAG::TARGET)] = true;		// プレイヤー通常攻撃ターゲット
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TARGET)][static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)][static_cast<int>(CollisionTags::TAG::TARGET)] = true;			// プレイヤーショット攻撃ターゲット
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TARGET)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)][static_cast<int>(CollisionTags::TAG::TARGET)] = true;		// プレイヤースタンプ攻撃ターゲット
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TARGET)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)][static_cast<int>(CollisionTags::TAG::TARGET)] = true;				// テレポート攻撃ターゲット
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TARGET)][static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::AIRSLASH)][static_cast<int>(CollisionTags::TAG::TARGET)] = true;					// エアースラッシュ攻撃ターゲット
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TARGET)][static_cast<int>(CollisionTags::TAG::AIRSLASH)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::BLAST)][static_cast<int>(CollisionTags::TAG::TARGET)] = true;						// 爆破攻撃ターゲット
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TARGET)][static_cast<int>(CollisionTags::TAG::BLAST)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)][static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)] = true;		// プレイヤー通常攻撃宝箱
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)][static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)][static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)] = true;			// プレイヤーショット攻撃宝箱
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)][static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)] = true;		// プレイヤースタンプ攻撃宝箱
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)][static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)] = true;				// テレポート攻撃宝箱
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)][static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::AIRSLASH)][static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)] = true;					// エアースラッシュ攻撃宝箱
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)][static_cast<int>(CollisionTags::TAG::AIRSLASH)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::BLAST)][static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)] = true;						// 爆破攻撃宝箱
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TREASURE_CHEST)][static_cast<int>(CollisionTags::TAG::BLAST)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::ITEM_AVILITY)] = true;						// プレイヤーとアイテムアビリティ
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ITEM_AVILITY)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::ITEM_FOOD)] = true;							// プレイヤーとアイテム食べ物
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ITEM_FOOD)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::ITEM_MONEY)] = true;							// プレイヤーとアイテムお金
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ITEM_MONEY)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;
	
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::ITEM_TREASURE)] = true;						// プレイヤーとアイテム宝
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ITEM_TREASURE)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::BAMBOO)] = true;								// プレイヤーと竹
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::BAMBOO)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)][static_cast<int>(CollisionTags::TAG::BAMBOO)] = true;				// プレイヤー通常攻撃と竹
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::BAMBOO)][static_cast<int>(CollisionTags::TAG::PLAYER_ATTACK_NORMAL)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)][static_cast<int>(CollisionTags::TAG::BAMBOO)] = true;					// プレイヤーショットと竹
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::BAMBOO)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_SHOT)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)][static_cast<int>(CollisionTags::TAG::BAMBOO)] = true;				// プレイヤースタンプと竹
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::BAMBOO)][static_cast<int>(CollisionTags::TAG::PLAYER_AVILITY_STAMP)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)][static_cast<int>(CollisionTags::TAG::BAMBOO)] = true;						// テレポートと竹
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::BAMBOO)][static_cast<int>(CollisionTags::TAG::TELEPORT_EXIT)] = true;
}

void CollisionManager::InitColliderMatrix()
{
	// サイズの定義
	collisionFunctionMatrix_.resize(ColliderType::COLLIDER_TYPES, std::vector<std::function<bool(std::weak_ptr<ColliderBase>, std::weak_ptr<ColliderBase>)>>(ColliderType::COLLIDER_TYPES));

	// 特定の組み合わせの関数を代入
	//collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::ARRAY)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
	//	[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
	//	{
	//		return IsHitCheckArrayToCircle(collider1, collider2);
	//	};

	//collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::ARRAY)][static_cast<int>(ColliderType::TYPE::BOX)] =
	//	[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
	//	{
	//		return IsHitCheckArrayToBox(collider1, collider2);
	//	};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::CIRCLE)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckCircleToCircle(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::CIRCLE)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckCircleToBox(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::CIRCLE)][static_cast<int>(ColliderType::TYPE::LINE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckCircleToLine(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::BOX)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckCircleToBox(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::BOX)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckBoxToBox(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::BOX)][static_cast<int>(ColliderType::TYPE::LINE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckBoxToLine(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::LINE)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckCircleToLine(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::LINE)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckBoxToLine(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::LINE)][static_cast<int>(ColliderType::TYPE::LINE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckLineToLine(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::CIRCLE)][static_cast<int>(ColliderType::TYPE::FAN)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckCircleToFan(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::FAN)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckCircleToFan(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::BOX)][static_cast<int>(ColliderType::TYPE::FAN)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckBoxToFan(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::FAN)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckBoxToFan(collider1, collider2);
		};
}

bool CollisionManager::IsHitCheckArrayToCircle(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckArrayToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckCircleToCircle(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	std::weak_ptr<ColliderCircle> colliderCircle1;
	std::weak_ptr<ColliderCircle> colliderCirlce2;

	// サークルコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::CIRCLE) { colliderCircle1 = std::dynamic_pointer_cast<ColliderCircle>(collider1.lock()); }
	if (collider2.lock()->GetType() == ColliderType::TYPE::CIRCLE) { colliderCirlce2 = std::dynamic_pointer_cast<ColliderCircle>(collider2.lock()); }
	
	// 情報の取得
	Vector2F center1 = colliderCircle1.lock()->GetPos();
	const float radius1 = colliderCircle1.lock()->GetRadius();
	Vector2F center2 = colliderCirlce2.lock()->GetPos();
	const float radius2 = colliderCirlce2.lock()->GetRadius();
	Vector2 hitPos = {};

	// 衝突判定
	const bool isHit = UtilityCollision::IsHitCircleToCircle(
		center1.ToVector2(),
		radius1,
		center2.ToVector2(),
		radius2,
		hitPos);

	if (isHit)
	{
		colliderCircle1.lock()->SetHitPos(hitPos);
		colliderCircle1.lock()->SetHitPos(hitPos);
	}

	// 衝突しているか返す
	return isHit;
}

bool CollisionManager::IsHitCheckCircleToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	std::weak_ptr<ColliderCircle> colliderCircle;
	std::weak_ptr<ColliderBox> colliderBox;

	// サークルコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::CIRCLE) { colliderCircle = std::dynamic_pointer_cast<ColliderCircle>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::CIRCLE) { colliderCircle = std::dynamic_pointer_cast<ColliderCircle>(collider2.lock()); }

	// ボックスコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::BOX) { colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::BOX) { colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider2.lock()); }

	// 情報の取得
	Vector2F top = colliderBox.lock()->GetAABBMin();
	Vector2F bottom = colliderBox.lock()->GetAABBMax();
	Vector2F centerF = colliderCircle.lock()->GetPos();
	const Vector2 center = centerF.ToVector2();
	const float radius = colliderCircle.lock()->GetRadius();
	Vector2 hitPos = {};

	// 衝突判定
	const bool isHit = UtilityCollision::IsHitCircleToBox(
		center,
		radius,
		top.ToVector2(),
		bottom.ToVector2(),
		hitPos);

	if (isHit)
	{
		colliderCircle.lock()->SetHitPos(hitPos);
		colliderBox.lock()->SetHitPos(hitPos);
	}

	// 衝突しているか返す
	return isHit;
}

bool CollisionManager::IsHitCheckCircleToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckCircleToFan(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	std::weak_ptr<ColliderCircle> colliderCircle;
	std::weak_ptr<ColliderFan> colliderFan;

	// サークルコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::CIRCLE) { colliderCircle = std::dynamic_pointer_cast<ColliderCircle>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::CIRCLE) { colliderCircle = std::dynamic_pointer_cast<ColliderCircle>(collider2.lock()); }

	// ファンコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::FAN) { colliderFan = std::dynamic_pointer_cast<ColliderFan>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::FAN) { colliderFan = std::dynamic_pointer_cast<ColliderFan>(collider2.lock()); }

	Vector2F circlePos = colliderCircle.lock()->GetPos();
	const float  circleRadius = colliderCircle.lock()->GetRadius();
	Vector2F fanPos = colliderFan.lock()->GetPos();
	const float fanRadius = colliderFan.lock()->GetRadius();
	const float baseAngle = colliderFan.lock()->GetBaseAngle();
	const float viewAngle = colliderFan.lock()->GetViewAngle();
	Vector2 hitPos = {};

	// 衝突判定
	const bool isHit = UtilityCollision::IsHitCircleToFan(
		circlePos.ToVector2(),
		circleRadius,
		fanPos.ToVector2(),
		fanRadius,
		baseAngle,
		viewAngle,
		hitPos);

	// 衝突しているか返す
	return isHit;
}

bool CollisionManager::IsHitCheckBoxToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	std::weak_ptr<ColliderBox> colliderBox1;
	std::weak_ptr<ColliderBox> colliderBox2;

	// ボックスコライダーの用意
	colliderBox1 = std::dynamic_pointer_cast<ColliderBox>(collider1.lock()); 
	colliderBox2 = std::dynamic_pointer_cast<ColliderBox>(collider2.lock()); 


	Vector2F axis4[4] = {
		colliderBox1.lock()->GetAxisX(),
		colliderBox1.lock()->GetAxisY(),
		colliderBox2.lock()->GetAxisX(),
		colliderBox2.lock()->GetAxisY()
	};

	for (const Vector2F axis : axis4)
	{
		if (!colliderBox1.lock()->OverlapOnAxis(colliderBox2, axis))
		{
			return false;
		}
	}

	// 簡易敵に衝突位置を計算
	Vector2F hitPosF;
	Vector2F pos1 = colliderBox1.lock()->GetOwner().GetParameter().pos_;
	Vector2F pos2 = colliderBox2.lock()->GetOwner().GetParameter().pos_;
	hitPosF.x = (pos1.x + pos2.x) * 0.5f;
	hitPosF.y = (pos1.y + pos2.y) * 0.5f;

	// 衝突位置格納
	Vector2 hitPos = hitPosF.ToVector2();
	colliderBox1.lock()->SetHitPos(hitPos);
	colliderBox2.lock()->SetHitPos(hitPos);

	return true;
}

bool CollisionManager::IsHitCheckBoxToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckBoxToFan(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	std::weak_ptr<ColliderBox> colliderBox;
	std::weak_ptr<ColliderFan> colliderFan;

	// ボックスコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::BOX) { colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::BOX) { colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider2.lock()); }
	
	// ファンコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::FAN) { colliderFan = std::dynamic_pointer_cast<ColliderFan>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::FAN) { colliderFan = std::dynamic_pointer_cast<ColliderFan>(collider2.lock()); }

	Vector2F top = colliderBox.lock()->GetAABBMin();
	Vector2F bottom = colliderBox.lock()->GetAABBMax();
	Vector2F fanPos = colliderFan.lock()->GetPos();
	const float radius = colliderFan.lock()->GetRadius();
	const float baseAngle = colliderFan.lock()->GetBaseAngle();
	const float viewAngle = colliderFan.lock()->GetViewAngle();
	Vector2 hitPos = {};

	// 衝突判定
	const bool isHit = UtilityCollision::IsHitBoxToFan(
		top.ToVector2(),
		bottom.ToVector2(),
		fanPos.ToVector2(),
		radius,
		baseAngle,
		viewAngle,
		hitPos);

	// 衝突しているか返す
	return isHit;
}

bool CollisionManager::IsHitCheckLineToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}