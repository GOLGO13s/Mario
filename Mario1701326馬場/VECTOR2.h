#pragma once
class VECTOR2
{
public:
	int Flag;
	VECTOR2();
	VECTOR2(int x, int y);
	~VECTOR2();
	int x;
	int y;
	int image;
	// 代入演算子
	VECTOR2& operator = (const VECTOR2& vec);	//演算子として使わない場合先頭に"operator"をつける
												// 添え字演算子
	int& operator[](int i);	//ｘが0ｙが1　それ以外はｘ

							//比較演算子
	bool operator == (const VECTOR2& vec) const;		//true falseのブール型を返す
	bool operator != (const VECTOR2& vec) const;

	//単項演算子
	VECTOR2& operator += (const VECTOR2& vec);	//値を書き換えられないようにconstをつける
	VECTOR2& operator -= (const VECTOR2& vec);	//値を書き換えられないようにconstをつける
	VECTOR2& operator *= (int k);
	VECTOR2& operator /= (int k);
	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
};

//	ベクトルの演算
// VECTOR2 + VECTOR2
//返り値の型　operator　演算子（引数1、…）;
VECTOR2 operator +(const VECTOR2& i, const VECTOR2& j);
// int + VECTOR2
VECTOR2 operator +(int j, const VECTOR2& i);
// VECTOR2 - VECTOR2
VECTOR2 operator -(const VECTOR2& i, const VECTOR2& j);
// int * VECTOR2
VECTOR2 operator *(int j, const VECTOR2& i);
// VECTOR2 *int
VECTOR2 operator *(const VECTOR2& i, int j);
// VECTOR2 / int
VECTOR2 operator /(const VECTOR2& i, int j);

VECTOR2 operator %(const VECTOR2& i, int j);