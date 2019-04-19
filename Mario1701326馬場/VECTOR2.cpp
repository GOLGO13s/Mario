#include "VECTOR2.h"

VECTOR2::VECTOR2()
{
	x = 0;
	y = 0;
}

VECTOR2::VECTOR2(int x, int y)
{
	this->x = x;	
	this->y = y;
}

VECTOR2::~VECTOR2()
{
}

// 代入演算子
VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)	//&は参照参照渡し
{
	this->x = vec.x;	//参照で受け取る場合はコンマ
	this->y = vec.y;
	return *this;		//参照で返す際はアドレスではなく実体を返す
}

// 添え字演算子
int & VECTOR2::operator[](int i)
{
	if (i == 0) {
		//return this->x;
		return x;
	}
	else if(i == 1) {
		//return this->y;
		return y;
	}
	else {
		//return this->x;
		return x;
	}
	
}


//比較演算子
bool VECTOR2::operator==(const VECTOR2 & vec) const
{
	return((this->x == vec.x) && (this->y == vec.y));
	
}
//比較演算子
bool VECTOR2::operator!=(const VECTOR2 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}


//単項演算子
VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;	
	this->y += vec.y;
	return *this;
}
//単項演算子
VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
//単項演算子
VECTOR2 & VECTOR2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return *this;
}
//単項演算子
VECTOR2 & VECTOR2::operator/=(int k)
{
	this->x /= k;
	this->y /= k;
	return *this;
}
//単項演算子
VECTOR2 VECTOR2::operator+() const
{
	return *this;
}
//単項演算子
VECTOR2 VECTOR2::operator-() const
{
	//	もう一つの書き方
	/*VECTOR2 vec;
	vec.x = -this->x;
	vec.y = -this->y;
	return vec;*/

	return VECTOR2(-this->x,-this->y);
}

VECTOR2 operator+(const VECTOR2 & i, const VECTOR2 & j)
{
	VECTOR2 vec;
	vec.x = i.x + j.x;
	vec.y = i.y + j.y;
	return vec;
	// 一行で書く方法
	//return VECTOR2(i.x + j.x, i.y + j.y);

}

VECTOR2 operator+(int j, const VECTOR2 & i)
{
	VECTOR2 vec;
	vec.x = j + i.x;
	vec.y = j + i.y;
	return vec;
}

VECTOR2 operator-(const VECTOR2 & i, const VECTOR2 & j)
{
	VECTOR2 vec;
	vec.x = i.x - j.x;
	vec.x = i.y - j.y;
	return vec;
	// 一行で書く方法
	//return VECTOR2(i.x - j.x, i.y - j.y);
}

VECTOR2 operator*(int j, const VECTOR2 & i)
{
	VECTOR2 vec;
	vec.x = j * i.x;
	vec.y = j * i.y;
	return vec;
	// 一行で書く方法
	//return VECTOR2(j * i.x,j * i.y);
}

VECTOR2 operator*(const VECTOR2 & i, int j)
{
	VECTOR2 vec;
	vec.x = i.x * j;
	vec.y = i.y *j;
	return vec;
	// 一行で書く方法
	//return VECTOR2(i.x * j, i.y * j);
}

VECTOR2 operator/(const VECTOR2 & i, int j)
{
	VECTOR2 vec;
	vec.x = i.x / j;
	vec.y = i.y / j;
	return vec;
	// 一行で書く方法
	//return VECTOR2(i.x / j, i.y / j);
}

VECTOR2 operator%(const VECTOR2 & i, int j)
{
	VECTOR2 vec;
	vec.x = i.x % j;
	vec.y = i.y % j;
	return vec;

}
