#include "../../Object/Character/Player.h"
#include "ComponentAvilityGiant.h"

ComponentAvilityGiant::ComponentAvilityGiant(Player& owner) :
	ComponentAvilityBase(owner)
{
	// 種類の設定
	type_ = AvilityTypes::TYPE::GIANT;
}

ComponentAvilityGiant::~ComponentAvilityGiant()
{
}

void ComponentAvilityGiant::Create()
{	
	// 巨大化前のサイズから位置のオフセットを計算するため、先に計算を行う
	float sizeY = static_cast<float>(parameter_.hitSize_.y);
	float offset = (sizeY * SCALE - sizeY) / 2.0f;
	parameter_.pos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(parameter_.GetUp(), offset));

	// 先にサイズを変更する前の scale_ で各半径やサイズを乗算
	parameter_.hitRadius_ *= (parameter_.scale_ + SCALE) / parameter_.scale_;
	parameter_.defaultAttackRadius_ *= (parameter_.scale_ + SCALE) / parameter_.scale_;
	parameter_.hitSize_ = Vector2F::MulVector2FFloat(parameter_.hitSize_.ToVector2F(), (parameter_.scale_ + SCALE) / parameter_.scale_).ToVector2();

	// 最後にスケールを更新
	parameter_.scale_ += SCALE;

	// 基底クラスの処理
	ComponentAvilityBase::Create();

	// 初期化
	Init();
}

void ComponentAvilityGiant::Init()
{

}

void ComponentAvilityGiant::Update()
{

}

void ComponentAvilityGiant::Remove()
{
	// スケールを引く前の状態でサイズや半径を除算して元に戻す
	float restoreRate = parameter_.scale_ / (parameter_.scale_ - SCALE);
	parameter_.hitRadius_ /= restoreRate;
	parameter_.defaultAttackRadius_ /= restoreRate;
	parameter_.hitSize_ = Vector2F::DivVector2F(parameter_.hitSize_.ToVector2F(), Vector2F(restoreRate, restoreRate)).ToVector2();

	// スケールを元に戻す
	parameter_.scale_ -= SCALE;

	// 地面に埋まらないようにずらした位置を元に戻す（下にずらす）
	float sizeY = static_cast<float>(parameter_.hitSize_.y);
	float offset = (sizeY * SCALE - sizeY) / 2.0f;
	parameter_.pos_ = Vector2F::SubVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(parameter_.GetUp(), offset));

	// 基底クラスの処理
	ComponentAvilityBase::Remove();
}