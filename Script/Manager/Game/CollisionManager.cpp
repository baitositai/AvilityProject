#include "../../Collider/ColliderBase.h"
#include "../../Object/ActorBase.h"
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
		// 所有者が非活動状態の場合
		if (!colliders_[i]->GetOwner().IsActive())
		{
			// 次へ
			continue;
		}

		for (int j = i + 1; j < size; j++)
		{
			auto& collider = colliders_[i];
			auto& collider2 = colliders_[j];

			// 所有者が非活動状態の場合
			if (!colliders_[j]->GetOwner().IsActive())
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
}

void CollisionManager::InitTagMatrix()
{
}

void CollisionManager::InitColliderMatrix()
{
	// サイズの定義
	collisionFunctionMatrix_.resize(ColliderType::COLLIDER_TYPES, std::vector<std::function<bool(std::weak_ptr<ColliderBase>, std::weak_ptr<ColliderBase>)>>(ColliderType::COLLIDER_TYPES));

	// 特定の組み合わせの関数を代入
	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::CIRCLE)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckCircleToCircle(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::CIRCLE)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckCircleToBox(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::CIRCLE)][static_cast<int>(ColliderType::TYPE::LINE)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckCircleToLine(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::BOX)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckCircleToCircle(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::BOX)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckBoxToBox(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::BOX)][static_cast<int>(ColliderType::TYPE::LINE)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckBoxToLine(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::LINE)][static_cast<int>(ColliderType::TYPE::CIRCLE)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckCircleToLine(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::LINE)][static_cast<int>(ColliderType::TYPE::BOX)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckBoxToLine(collA, collB);
		};

	collisionFunctionMatrix_[static_cast<int>(ColliderType::TYPE::LINE)][static_cast<int>(ColliderType::TYPE::LINE)] =
		[this](std::weak_ptr<ColliderBase> collA, std::weak_ptr<ColliderBase> collB) -> bool
		{
			return IsHitCheckLineToLine(collA, collB);
		};
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
	return false;
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