#pragma once
#include "VECTOR2.h"
#include "VECTOR3.h"

class Enemy
{
private:
	VECTOR3 pos;
	VECTOR2 size;
	float speed;
	bool lrFlag;
	bool deadFlag;
	int animCnt;
public:
	Enemy();
	~Enemy();
	void SystemInit();	//画像読み込み
	void Init();		//パラメータ初期化
	void Update();		//移動処理
	void Draw();		//描画処理
	RECT e;

	//座標を返す
	VECTOR3&GetPos() {
		return pos;
	}

	//posをセットする
	VECTOR3& SetPos(VECTOR3 pos) {
		this->pos = pos;
		return pos;
	}
	
	//静止時と移動時のサイズを返す
	VECTOR2&GetSize() {
		return size;

	}

	//死亡フラグを返す
	bool GetDeadFlag() {
		return deadFlag;
	}
	//死亡フラグをセットする
	void SetDeadFlag(bool flag) {
		if (flag == true) {
			deadFlag = true;//死亡
		}
		else {
			deadFlag = false;//生きている
		}
	}

};

