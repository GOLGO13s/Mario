#include "DxLib.h"
#include "Field.h"

// マップのデータ
	int MapData[MAP_HEIGHT][MAP_WIDTH] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,33,34,35,36,37,38,39,40,41,42,43,44,45,46,0},
		{48,49,50,0,0,0,0,0,0,0,0,0,60,61,62,63},
		{64,65,0,0,0,0,0,0,0,0,0,0,0,77,78,79},
		{80,80,80,80,80,80,80,0,0,80,80,80,80,80,80,80},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{128,129,0,0,132,132,132,132,132,132,132,132, 0,  0, 142,143},
		{144,145,0,0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 158,159},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{177,177,177,177,176,0,0,183,184,0,0,186,187,187,187,187},
		{0,0,0,0,0,0,0,199,200,0,0,0,0,0,0,0},
		{208,209,0,0,0,0,0,0,0,0,0,0,0,221,222,223},
		{224,225,226,227,227,227,227,227,227,227,227,227,227,227,238,239},
		{240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255},

	};

Field::Field()
{
	Init();
}


Field::~Field()
{

}

void Field::Init()
{	
	//マップチップ読み込み
	LoadDivGraph("image/brock1.png", 256, 16, 16, 32, 32, chip);
	//RECT
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			m[y][x].left = (MapData[y][x] % MAP_WIDTH) * MAP_CHIP_SIZE;
			m[y][x].right = m[y][x].left + MAP_CHIP_SIZE;
			m[y][x].top = (MapData[y][x] / MAP_WIDTH) * MAP_CHIP_SIZE;
			m[y][x].bottom = m[y][x].top + MAP_CHIP_SIZE;
		}
	}
}

void Field::Draw()
{	
	//マップの描画
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			DrawGraph(x * MAP_CHIP_SIZE, y * MAP_CHIP_SIZE, chip[MapData[y][x]], false);
			/*デバッグ用*/
		/*	if ((MapData[y][x] == 0)||(MapData[y][x] == 199)||(MapData[y][x] == 200)) {
				DrawBox(x * MAP_CHIP_SIZE, y * MAP_CHIP_SIZE,
					x * MAP_CHIP_SIZE + MAP_CHIP_SIZE, y * MAP_CHIP_SIZE + MAP_CHIP_SIZE,
					GetColor(255,255,255), TRUE);
			}*/
		}
	}
}

int Field::GetMapData(float X, float Y)
{
	int x, y;

	// 整数値へ変換
	x = (int)X / MAP_CHIP_SIZE;
	y = (int)Y / MAP_CHIP_SIZE;

	// マップからはみ出ていたら 0 を返す
	if (x >= MAP_WIDTH || y >= MAP_HEIGHT || x < 0 || y < 0) return 0;

	// 指定の座標に該当するマップの情報を返す
	return MapData[y][x];
}
