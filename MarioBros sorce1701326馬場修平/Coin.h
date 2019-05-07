#pragma once
#include "VECTOR2.h"
#include "VECTOR3.h"

class Coin
{
private:
	VECTOR3 pos;
	VECTOR2 size;
	int animCnt;
	bool getFlag;
public:
	Coin();
	~Coin();
	void SystemInit();	//画像読み込み
	void Init();		//パラメータ初期化
	void Draw();		//描画処理
	RECT c;					
	//座標を返す
	VECTOR3&GetPos() {
		return pos;
	}

	//posをセットする
	VECTOR3& SetPos(VECTOR3 pos) {
		this->pos = pos;
		return pos;
	}

	//画像サイズを返す
	VECTOR2&GetSize() {
		return size;
	}

	//ゲットフラグを返す
	bool GetCoinFlag() {
		return getFlag;
	}
	//ゲットフラグをセットする
	void SetCoinFlag(bool flag) {
		if (flag == true) {
			getFlag = true;//死亡
		}
		else {
			getFlag = false;//生きている
		}
	}
};

