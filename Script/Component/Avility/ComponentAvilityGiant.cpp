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
	// 大きさを変更
	parameter_.scale_ = SCALE;
	parameter_.hitRadius_ *= SCALE;
	parameter_.defaultAttackRadius_ *= SCALE;
	parameter_.hitSize_ = Vector2F::MulVector2FFloat(parameter_.hitSize_.ToVector2F(), SCALE).ToVector2();	
	
	// 地面に埋まらないように位置をずらす
	float sizeY = static_cast<float>(parameter_.hitSize_.y);
	float offset = (sizeY * SCALE - sizeY) / 2.0f;
	parameter_.pos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(parameter_.GetUp(), offset));

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
	// 大きさを戻す
	parameter_.scale_ = 1.0f;
	parameter_.hitRadius_ /= SCALE;
	parameter_.defaultAttackRadius_ /= SCALE;
	parameter_.hitSize_ = Vector2F::DivVector2F(parameter_.hitSize_.ToVector2F(), Vector2F(SCALE, SCALE)).ToVector2();

	// 基底クラスの処理
	ComponentAvilityBase::Remove();
}