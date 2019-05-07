#pragma once
#include "VECTOR2.h"
#include "VECTOR3.h"

class Enemy
{
private:
	VECTOR3 pos;
	VECTOR2 size;
	float G;
	float speed;
	int animCnt;
	
	bool lrFlag;
	bool dyingFlag;	//瀕死状態フラグ(敵は消さない)
	bool deathFlag;	//死亡状態フラグ(敵を消す)
	bool getcoinFlag;
	bool ehitBFlag;
	bool movFlag;
public:
	Enemy();
	~Enemy();
	void SystemInit();	//画像読み込み
	void Init();		//パラメータ初期化
	void Update();		//移動処理
	void Draw();		//描画処理
	RECT e;
	int revivalCnt;
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
	bool GetDyingFlag() {
		return dyingFlag;
	}
	//死亡フラグをセットする
	void SetDyingFlag(bool flag) {
		if (flag == true) {
			dyingFlag = true;//死亡
		}
		else {
			dyingFlag = false;//生きている
		}
	}

	//死亡フラグを返す
	bool GetDeathFlag() {
		return deathFlag;
	}

	//死亡フラグをセットする
	void SetDeathFlag(bool flag) {
		if (flag == true) {
			deathFlag = true;//死亡
		}
		else {
			deathFlag = false;//生きている
		}
	}

	//死亡フラグを返す
	bool GetEHitBFlag() {
		return ehitBFlag;
	}
	//死亡フラグをセットする
	void SetEHitBFlag(bool flag) {
		if (flag == true) {
			ehitBFlag = true;//死亡
		}
		else {
			ehitBFlag = false;//生きている
		}
	}

};

