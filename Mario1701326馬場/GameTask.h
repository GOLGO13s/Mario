#pragma once

class Field;
class Player;
class Enemy;
class HitCheck;

//画面遷移用
enum GAME_MODE 
{
	GAME_INIT,
	GAME_TITLE,
	GAME_MAIN,
	GAME_OVER,
	GAME_CLEAR
};

class GameTask
{
private:
	GameTask(); //コンストラクタ(シングルトン))
	GameTask(const GameTask&) {}		//コピーコンストラクタのprivate化
	GameTask operator=(const GameTask&) {}	//代入をprivate化
	~GameTask();//デストラクタ
public:
	static GameTask&GetInstance() {
		static GameTask gInst;
		return gInst;
	}
	int SystemInit(void);	//システム初期化
	int GameUpDate(void);	//ゲームループメイン

	static int SCREEN_SIZE_X;
	static int SCREEN_SIZE_Y;

private:
	int GameInit(void);
	int GameTitle(void);
	int GameMain(void);
	int GameOver(void);
	int GameClear(void);
	void LifeRender(void);
	GAME_MODE gameMode;
	int newKey;
	int oldKey;
	int trgKey;
	int life;
	Field*field;	//フィールドのオブジェクト管理
	Player*player;	//プレイヤーのオブジェクト管理
	Enemy*enemy;	//エネミーのオブジェクト管理
	HitCheck*hit;
};
