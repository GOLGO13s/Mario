#include "VECTOR3.h"



VECTOR3::VECTOR3()
{
	x = 0;
	y = 0;
}

VECTOR3::VECTOR3(float x, float y)
{
	this->x = x;
	this->y = y;
}


VECTOR3::~VECTOR3()
{
}

VECTOR3 & VECTOR3::operator=(const VECTOR3 & vec)
{
	this->x = vec.x;	//参照で受け取る場合はコンマ
	this->y = vec.y;
	return *this;		//参照で返す際はアドレスではなく実体を返す
}

float & VECTOR3::operator[](float i)
{
	if (i == 0) {
		//return this->x;
		return x;
	}
	else if (i == 1) {
		//return this->y;
		return y;
	}
	else {
		//return this->x;
		return x;
	}
}

bool VECTOR3::operator==(const VECTOR3 & vec) const
{
	return((this->x == vec.x) && (this->y == vec.y));
}

bool VECTOR3::operator!=(const VECTOR3 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

VECTOR3 & VECTOR3::operator+=(const VECTOR3 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

VECTOR3 & VECTOR3::operator-=(const VECTOR3 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

VECTOR3 & VECTOR3::operator*=(float k)
{
	this->x *= k;
	this->y *= k;
	return *this;
}

VECTOR3 & VECTOR3::operator/=(float k)
{
	this->x /= k;
	this->y /= k;
	return *this;
}

VECTOR3 VECTOR3::operator+() const
{
	return *this;
}

VECTOR3 VECTOR3::operator-() const
{
	//	もう一つの書き方
	/*VECTOR3 vec;
	vec.x = -this->x;
	vec.y = -this->y;
	return vec;*/

	return VECTOR3(-this->x, -this->y);
}

VECTOR3 operator+(const VECTOR3 & i, const VECTOR3 & j)
{
	VECTOR3 vec;
	vec.x = i.x + j.x;
	vec.y = i.y + j.y;
	return vec;
	// 一行で書く方法
	//return VECTOR3(i.x + j.x, i.y + j.y);
}

VECTOR3 operator+(float j, const VECTOR3 & i)
{
	VECTOR3 vec;
	vec.x = j + i.x;
	vec.y = j + i.y;
	return vec;
}

VECTOR3 operator-(const VECTOR3 & i, const VECTOR3 & j)
{
	VECTOR3 vec;
	vec.x = i.x - j.x;
	vec.x = i.y - j.y;
	return vec;
	// 一行で書く方法
	//return VECTOR3(i.x - j.x, i.y - j.y);
}

VECTOR3 operator*(float j, const VECTOR3 & i)
{
	VECTOR3 vec;
	vec.x = j * i.x;
	vec.y = j * i.y;
	return vec;
	// 一行で書く方法
	//return VECTOR3(j * i.x,j * i.y);
}

VECTOR3 operator*(const VECTOR3 & i, float j)
{
	VECTOR3 vec;
	vec.x = i.x * j;
	vec.y = i.y *j;
	return vec;
	// 一行で書く方法
	//return VECTOR3(i.x * j, i.y * j);
}

VECTOR3 operator/(const VECTOR3 & i, float j)
{
	VECTOR3 vec;
	vec.x = i.x / j;
	vec.y = i.y / j;
	return vec;
	// 一行で書く方法
	//return VECTOR3(i.x / j, i.y / j);
}

VECTOR3 operator%(const VECTOR3 & i, float j)
{
	VECTOR3 vec;
	vec.x = (int)i.x % (int)j;
	vec.y = (int)i.y % (int)j;
	return vec;
}
