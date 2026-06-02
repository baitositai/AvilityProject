#include <cmath>
#include "Vector2.h"
#include "Vector2F.h"


//デフォルトコンストラクタ
Vector2F::Vector2F(void)
{
	x = 0.0F;
	y = 0.0F;
}


//コンストラクタ
Vector2F::Vector2F(float ix, float iy)
{
	x = ix;
	y = iy;
}


//デストラクタ
Vector2F::~Vector2F(void)
{

}


//Vector2へ変換する関数
Vector2 Vector2F::ToVector2(void)
{
	Vector2 ret;

	ret.x = static_cast<int>(roundf(x));
	ret.y = static_cast<int>(roundf(y));

	return ret;
}

float Vector2F::Length(void)const
{
	return std::sqrt(x * x + y * y);
}
Vector2F Vector2F::Normalize(void)
{
	float len = Length();
	return (len != 0) ? Vector2F(x / len, y / len) : Vector2F(0, 0);
}


//ベクトル線を作る
Vector2F Vector2F::CreateVectorLine(Vector2 value1, Vector2 value2)
{
	return Vector2F(static_cast<float>(value1.x - value2.x),
		static_cast<float>(value1.y - value2.y));
}

//Vector2F同士の比較
bool Vector2F::IsVector2F(Vector2F value1, Vector2F value2)
{
	if (value1.x < value2.x &&
		value1.y < value2.y)
	{
		return true;
	}

	return false;
}

bool Vector2F::IsSameVector2F(const Vector2F value1, const Vector2F value2)
{
	if (value1.x == value2.x && value1.y == value2.y)
	{
		return true;
	}
	return false;
}

Vector2F Vector2F::AddVector2F(Vector2F value1, Vector2F value2)
{
	Vector2F ret;
	ret.x = value1.x + value2.x;
	ret.y = value1.y + value2.y;
	return ret;
}

Vector2F Vector2F::SubVector2F(Vector2F value1, Vector2F value2)
{
	Vector2F ret;
	ret.x = value1.x - value2.x;
	ret.y = value1.y - value2.y;
	return ret;
}

Vector2F Vector2F::MulVector2F(Vector2F value1, Vector2F value2)
{
	Vector2F ret;
	ret.x = value1.x * value2.x;
	ret.y = value1.y * value2.y;
	return ret;
}

Vector2F Vector2F::DivVector2F(Vector2F value1, Vector2F value2)
{
	Vector2F ret;
	ret.x = value1.x / value2.x;
	ret.y = value1.y / value2.y;
	return ret;
}

Vector2F Vector2F::MulVector2FFloat(Vector2F value1, float value2)
{
	value1.x *= value2;
	value1.y *= value2;
	return value1;
}

Vector2F Vector2F::Distance(const Vector2F& value1, const Vector2F& value2)
{
	Vector2F distance;
	distance.x = abs(value1.x - value2.x);
	distance.y = abs(value1.y - value2.y);
	return distance;
}