#pragma once
#include "VECTOR2.h"

constexpr int MAP_CHIP_SIZE(32);	//マップチップの大きさ
constexpr int MAP_WIDTH(16);		//マップの幅(横)
constexpr int MAP_HEIGHT(16);		//マップの高さ(縦)

class Field
{
private:
	int chip[256];
public:
	RECT m[MAP_HEIGHT][MAP_WIDTH];	// 表示する矩形のセット
	Field();
	~Field();
	void Init();		//パラメータ初期化
	void Draw();		//描画処理
	int GetMapData(float X,float Y);	//マップデータの値を返す
};

