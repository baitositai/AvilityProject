#include "../../Collider/ColliderBase.h"
#include "../../Collider/ColliderBox.h"
#include "../../Collider/ColliderCircle.h"
#include "../../Collider/ColliderLine.h"
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

	for (int i = 0; i < size - 1; i++)
	{
		// コライダーや所有者が非活動状態の場合
		if (!colliders_[i]->GetOwner().IsActive() || !colliders_[i]->IsActive())
		{
			// 次へ
			continue;
		}

		for (int j = i + 1; j < size; j++)
		{
			auto& collider = colliders_[i];
			auto& collider2 = colliders_[j];

			// 所有者が非活動状態の場合
			if (!colliders_[j]->GetOwner().IsActive() || !colliders_[i]->IsActive())
			{
				// 次へ
				continue;
			}

			// 各コライダーからタグを取得
			const auto& tag1 = colliders_[i]->GetTag();
			const auto& tag2 = colliders_[j]->GetTag();

			/*if (tag1 == CollisionTags::TAG::ANOMALY && tag2 == CollisionTags::TAG::REPORT ||
				tag1 == CollisionTags::TAG::REPORT && tag2 == CollisionTags::TAG::ANOMALY)
			{
				int a = 0;
			}*/

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
	// 中身が空の場合
	if (collider == nullptr)
	{
		// 追加しない
		return;
	}

	// コライダーの追加
	colliders_.push_back(collider);
}

void CollisionManager::Clear()
{
	// 中身の削除
	colliders_.clear();
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

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::STAGE)] = true;				// プレイヤーとステージ
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::STAGE)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::AVILITY_BOX)][static_cast<int>(CollisionTags::TAG::PLAYER)] = true;			//アビリティ設置ボックスとプレイヤー
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::PLAYER)][static_cast<int>(CollisionTags::TAG::AVILITY_BOX)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::AVILITY_BOX)][static_cast<int>(CollisionTags::TAG::STAGE)] = true;			//アビリティ設置ボックスとステージ
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::STAGE)][static_cast<int>(CollisionTags::TAG::AVILITY_BOX)] = true;

	collTagMatrix_[static_cast<int>(CollisionTags::TAG::AVILITY_BOX)][static_cast<int>(CollisionTags::TAG::ENEMY)] = true;			//アビリティ設置ボックスと敵
	collTagMatrix_[static_cast<int>(CollisionTags::TAG::ENEMY)][static_cast<int>(CollisionTags::TAG::AVILITY_BOX)] = true;
}

void CollisionManager::InitColliderMatrix()
{
	// サイズの定義
	collisionFunctionMatrix_.resize(ColliderType::COLLIDER_TYPES, std::vector<std::function<bool(std::weak_ptr<ColliderBase>, std::weak_ptr<ColliderBase>)>>(ColliderType::COLLIDER_TYPES));

	// 特定の組み合わせの関数を代入
	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::ARRAY)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckArrayToCircle(collider1, collider2);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::ARRAY)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2) -> bool
		{
			return IsHitCheckArrayToBox(collider1, collider2);
		};

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
			return IsHitCheckCircleToCircle(collider1, collider2);
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
}

bool CollisionManager::IsHitCheckArrayToCircle(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckArrayToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	std::weak_ptr<ColliderArray> colliderArray;
	std::weak_ptr<ColliderBox> colliderBox;

	// モデルコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::ARRAY) { colliderArray = std::dynamic_pointer_cast<ColliderArray>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::ARRAY) { colliderArray = std::dynamic_pointer_cast<ColliderArray>(collider2.lock()); }

	// カプセルコライダーの用意
	if (collider1.lock()->GetType() == ColliderType::TYPE::BOX) { colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider1.lock()); }
	else if (collider2.lock()->GetType() == ColliderType::TYPE::BOX) { colliderBox = std::dynamic_pointer_cast<ColliderBox>(collider2.lock()); }

	// 判定結果
	ColliderArray::Result result = {};

	const Vector2 top = colliderBox.lock()->GetLocalTopPos();
	const Vector2 bottom = colliderBox.lock()->GetLocalBottomPos();
	const auto arrayOfarray = colliderArray.lock()->GetArrayOfArrys();
	const auto ids = colliderArray.lock()->GetHitIds();
	const Vector2 size = colliderArray.lock()->GetChipSize();

	// 衝突判定
	bool isHit = UtilityCollision::IsHitArrayToBox(
		arrayOfarray,
		ids,
		size, 
		result,
		top, 
		bottom);

	// 判定結果を保存
	colliderArray.lock()->SetResult(result);

	// 衝突しているか返す
	return isHit;
}

bool CollisionManager::IsHitCheckCircleToCircle(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckCircleToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckCircleToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
}

bool CollisionManager::IsHitCheckBoxToBox(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	std::weak_ptr<ColliderBox> colliderBox1;
	std::weak_ptr<ColliderBox> colliderBox2;

	// モデルコライダーの用意
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

	return true;
}

bool CollisionManager::IsHitCheckBoxToLine(std::weak_ptr<ColliderBase> collider1, std::weak_ptr<ColliderBase> collider2)
{
	return false;
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