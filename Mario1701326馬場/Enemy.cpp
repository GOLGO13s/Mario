#include "DxLib.h"
#include "Chara_Base.h"
#include "Enemy.h"
#include "ImageMng.h"

Enemy::Enemy()
{
	SystemInit();
	Init();
}


Enemy::~Enemy()
{

}

void Enemy::SystemInit()
{
	//画像読み込み
	//enemy(亀)
	VECTOR2 divSize = { 29,32 };
	VECTOR2 divNum = { 3,1 };
	ImageMng::GetInstance().SetID("turtle", "image/enemy.png", divSize, divNum);
	ImageMng::GetInstance().SetID("turtle dead", "image/enemy2-1.png", divSize, divNum);
}

void Enemy::Init()
{
	//初期化
	pos.x = (219.0f);
	pos.y = (440.0f);
	size = { 29 ,32 };
	//RECT
	e.top = pos.y - size.y/2;
	e.bottom = pos.y + size.y/2;
	e.left = pos.x - size.x/2;
	e.right = pos.x + size.x / 2;

	speed = 2.0f;
	int Parme = GetRand(1);
	if(Parme == 0)lrFlag = false;		//false右向き,ture;左向き
	if(Parme == 1)lrFlag = true;
	deadFlag = false;
	animCnt = 0;
}

void Enemy::Update()
{
	if (pos.x + size.x/2 <= StartPos ) {
		
		pos.x = EndPos;
	}
	if (pos.x - size.x/2 >= EndPos) {
		pos.x = StartPos;
	}
	if (lrFlag == true) {
		pos.x -= speed;
	}
	else {
		pos.x += speed;
	}
	if (deadFlag == true) {
		speed = 0.0f;
	}
}

void Enemy::Draw()
{
	animCnt++;
	//アニメーション描画
	if (deadFlag == false) {
		ImageMng::GetInstance().DrawImage("turtle", pos.x - size.x / 2, pos.y - size.y / 2, animCnt / 7 % 3 == 0, true, lrFlag);
	}
	if (deadFlag == true) {
		ImageMng::GetInstance().DrawImage("turtle dead", pos.x - size.x / 2, pos.y - size.y / 2, animCnt / 7 % 3 == 0, true, lrFlag);
	}
}
