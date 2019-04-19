#pragma once
class VECTOR3
{
public:
	VECTOR3();
	VECTOR3(float x, float y);
	~VECTOR3();
	float x;
	float y;
	float image;
	// 代入演算子
	VECTOR3& operator = (const VECTOR3& vec);	//演算子として使わない場合先頭に"operator"をつける
												// 添え字演算子
	float& operator[](float i);	//ｘが0ｙが1　それ以外はｘ

							//比較演算子
	bool operator == (const VECTOR3& vec) const;		//true falseのブール型を返す
	bool operator != (const VECTOR3& vec) const;

	//単項演算子
	VECTOR3& operator += (const VECTOR3& vec);	//値を書き換えられないようにconstをつける
	VECTOR3& operator -= (const VECTOR3& vec);	//値を書き換えられないようにconstをつける
	VECTOR3& operator *= (float k);
	VECTOR3& operator /= (float k);
	VECTOR3 operator+()const;
	VECTOR3 operator-()const;
};

//	ベクトルの演算
// VECTOR3 + VECTOR3
//返り値の型　operator　演算子（引数1、…）;
VECTOR3 operator +(const VECTOR3& i, const VECTOR3& j);
// float + VECTOR3
VECTOR3 operator +(float j, const VECTOR3& i);
// VECTOR3 - VECTOR3
VECTOR3 operator -(const VECTOR3& i, const VECTOR3& j);
// float * VECTOR3
VECTOR3 operator *(float j, const VECTOR3& i);
// VECTOR3 *float
VECTOR3 operator *(const VECTOR3& i, float j);
// VECTOR3 / float
VECTOR3 operator /(const VECTOR3& i, float j);

VECTOR3 operator %(const VECTOR3& i, float j);


