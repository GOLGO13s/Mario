#pragma once
#include "VECTOR2.h"//int型
#include"VECTOR3.h"//float型

typedef struct
{
	VECTOR3 pos, mov, tmp;
	VECTOR2 size, bsize, jsize,dsize;
	bool walkFlag;
	bool lrFlag;
	bool jumpFlag;
	bool brakeFlag;
	bool damageFlag;
	bool hitTFlag;
	bool hitBFlag;
}PLAYER;

class Player 
{
private:
	int animCnt;
	float jumppow, pow, G;
public:
	Player();
	~Player();
	void SystemInit();		//画像読み込み
	void Init();			//パラメータ初期化
	void Update();			//移動処理
	void Draw();			//描画処理
	void Damage();			//ライフが減った時の処理
	void HitMapTop();		//マップと当たった時の判定(上辺)
	void HitMapBottom();	//マップと当たった時の判定(下辺)
	PLAYER player;
	RECT p;

	//動作フラグを返す(ウォーク)
	bool GetWalkFlag() {
		return player.walkFlag;
	}
	//ジャンプフラグを返す
	bool GetJumpFlag() {
		return player.jumpFlag;
	}
	//ジャンプフラグをセットする
	void SetJumpFlag(bool flag) {
		if (flag == true) {
			player.jumpFlag = true;//ジャンプ中
		}
		else {
			player.jumpFlag = false;//ジャンプ中じゃない
		}
	}
	//ブレーキ状態フラグを返す
	bool GetBrakeFlag() {
		return player.brakeFlag;
	}

	//座標を返す
	VECTOR3&GetPos() {
		return player.pos;
	}
	//posをセットする
	VECTOR3& SetPos(VECTOR3 pos) {
		this->player.pos = pos;
		return pos;
	}

	//移動値を返す
	VECTOR3&GetMov() {
		return player.mov;
	}
	//movをセットする
	VECTOR3& SetMov(VECTOR3 mov) {
		this->player.mov = mov;
		return mov;
	}

	//tmpを返す
	VECTOR3&GetTmp() {
		return player.tmp;
	}

	//静止時と移動時のサイズを返す
	VECTOR2&GetSize() {
		return player.size;

	}

	//ブレーキモーションの絵のサイズを返す
	VECTOR2&GetBSize() {
		return player.bsize;
	}

	//ジャンプモーションのサイズを返す
	VECTOR2&GetJSize() {
		return player.jsize;
	}
	
	//ダメージフラグを返す
	bool&GetDamageFlag() {
		return player.damageFlag;
	}

	//ダメージフラグをセットする
	void SetDamageFlag(bool flag) {
		if (flag == true) {
			player.damageFlag = true;//ダメージを食らった
		}
		else {
			player.damageFlag = false;//ダメージを食らっていない
		}
	}

	//ヒットフラグを返す
	bool&GetHitBFlag() {
		return player.hitBFlag;
	}

	//ヒットフラグをセットする
	void SetHitBFlag(bool flag) {
		if (flag == true) {
			player.hitBFlag = true;//当たっている
		}
		else {
			player.hitBFlag = false;//当たっていない
		}
	}

	//ヒットフラグを返す
	bool&GetHitTFlag() {
		return player.hitTFlag;
	}

	//ヒットフラグをセットする
	void SetHitTFlag(bool flag) {
		if (flag == true) {
			player.hitTFlag = true;//当たっている
		}
		else {
			player.hitTFlag = false;//当たっていない
		}
	}

	bool&GetLRFlag() {
		return player.lrFlag;
	}
};