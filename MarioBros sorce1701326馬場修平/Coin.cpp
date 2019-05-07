#include "DxLib.h"
#include "ImageMng.h"
#include "Coin.h"



Coin::Coin()
{
	SystemInit();
	Init();
}


Coin::~Coin()
{
}

void Coin::SystemInit()
{
	//エネミー画像読み込み
	//enemy(亀)
	VECTOR2 divSize = { 29,32 };
	VECTOR2 divNum = { 10,1 };
	ImageMng::GetInstance().SetID("coin", "image/coin.png", divSize, divNum);
}

void Coin::Init()
{
	pos.x = (0.0f);
	pos.y = (0.0f);
	size = { 29 ,32 };
	getFlag = false;
	//RECT
	c.top = pos.y - size.y / 2;
	c.bottom = pos.y + size.y / 2;
	c.left = pos.x - size.x / 2;
	c.right = pos.x + size.x / 2;
}

void Coin::Draw()
{
	if (getFlag == false) {
		ImageMng::GetInstance().DrawImage("coin", pos.x - size.x / 2, pos.y - size.y / 2, animCnt / 7 % 7 == 0, true, 1);
	}
}
