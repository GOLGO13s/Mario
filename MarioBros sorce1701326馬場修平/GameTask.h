#pragma once
#include <list>

class Field;
class Player;
class Enemy;
class Coin;
class HitCheck;

//画面遷移用
enum GAME_MODE 
{
	GAME_INIT,
	GAME_TITLE,
	GAME_DESCRIPTION,
	GAME_MAIN,
	GAME_OVER
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
	int GameInit(void);			//初期化や読み込みを行う
	int GameTitle(void);		//ゲームタイトル表示を行う
	int GameDescription(void);	//ゲーム説明を行う
	int GameMain(void);			//ゲームメインの処理を行う
	int GameOver(void);			//ゲームオーバの処理を行う
	void PlayerVSEnemy();
	void PlayerVSCoin();
	void PlayerVSMap(float x, float y ,float sx ,float sy);
	void PlayerVSPow(float x, float y, float sx, float sy);
	void EnemyVSMap(float x, float y, float sx, float sy);
	void LifeRender(void);
	GAME_MODE gameMode;
	int newKey;
	int oldKey;
	int trgKey;
	int life;
	int draw,Font;
	int graph;	//グラフィックハンドル
	int ecount;	//エネミーのカウント
	int score;	//スコア
	int ranking[3];
	Field*field;	//フィールドクラスのオブジェクト管理
	Player*player;	//プレイヤークラスのオブジェクト管理
	std::list<Enemy*> EnemyList;	//エネミクラスーのリスト管理;
	Coin*coin;		//コインクラスのオブジェクト管理
	HitCheck*hit;	//ヒットチェッククラスのオブジェクト管理
};
