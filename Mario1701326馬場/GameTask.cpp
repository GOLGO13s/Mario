#include "DxLib.h"
#include "GameTask.h"
#include "KeyMng.h"
#include "ImageMng.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "HitCheck.h"

//スクリーンのサイズ
int GameTask::SCREEN_SIZE_X = 512;
int GameTask::SCREEN_SIZE_Y = 512;

int GameTask::GameUpDate(void)
{
	//キー情報更新
	KeyMng::GetInstance().Update();

	switch (gameMode) {
	case GAME_INIT:
		GameInit();
		gameMode = GAME_TITLE;
		break;
	case GAME_TITLE:
		GameTitle();
		if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_MAIN;
		break;
	case GAME_MAIN:
		GameMain();
		if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_CLEAR;
		break;
	case GAME_OVER:
		GameOver();
		if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_INIT;
		break;
	case GAME_CLEAR:
		GameClear();
		if (KeyMng::GetInstance().trgKey[P1_ENTER]) gameMode = GAME_INIT;
		break;
	}
	return 0;
}

//コンストラクタ
GameTask::GameTask()
{
	SystemInit();
	gameMode = GAME_INIT;
	oldKey = 0;
}

//デストラクタ
GameTask::~GameTask()
{
	
}

//-----システム初期化
int GameTask::SystemInit(void)
{
	SetWindowText("マリオブラザーズ 1701326馬場修平");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

int GameTask::GameInit(void)
{
	//フィールドのクラスのインスタンス
	if (field == nullptr)field = new Field();
	//プレイヤークラスのインスタンス
	if (player == nullptr)player = new Player();
	//エネミークラスにンスタンス化
	if (enemy == nullptr)enemy = new Enemy();
	if (hit == nullptr)hit = new HitCheck();
	//画像読み込み
	ImageMng::GetInstance().SetID("title", "image/title.png");
	ImageMng::GetInstance().SetID("life", "image/life2.png");
	//初期化
	life = 2;
	return 0;
}

//タイトル画面
int GameTask::GameTitle(void)
{
	int title_X = 0,title_Y = 0;
	ImageMng::GetInstance().DrawImage("title",title_X, title_Y, true, 1);
	DrawString(200, 480, "START ENTER", GetColor(255, 255, 255));
	return 0;
}

//-----ゲーム画面
int GameTask::GameMain(void)
{
	//フィールドの描画
	if (field != nullptr) {
		field->Draw();
	}
	
	//プレイヤーの更新
	if (player != nullptr) {
		player->Update();
		player->Draw();
	}
	//エネミーの更新と描画
	if (enemy != nullptr) {
		enemy->Update();
		enemy->Draw();
	}

	// データの準備
	//キャラクタ画像の矩形とｘ，ｙ座標を元に左上右下座標データを作成し、当たり判定に利用する。
	//プレイヤー
	if (player != nullptr) {
		int p_width = player->p.right - player->p.left;
		int p_height = player->p.bottom - player->p.top;
		SetRect(&player->p, player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2,
			player->GetPos().x + p_width / 2, player->GetPos().y + p_height / 2);
		//RECTの範囲を描画
		DrawBox(player->p.left, player->p.top, player->p.right, player->p.bottom, GetColor(255, 0, 0), false);
	}
	//エネミー
	if (enemy != nullptr) {
		int e_width = enemy->e.right - enemy->e.left;
		int e_height = enemy->e.bottom - enemy->e.top;
		SetRect(&enemy->e, enemy->GetPos().x - enemy->GetSize().x / 2, enemy->GetPos().y - enemy->GetSize().y / 2,
			enemy->GetPos().x + e_width / 2, enemy->GetPos().y + e_height / 2);
		//RECTの範囲を描画
		DrawBox(enemy->e.left, enemy->e.top, enemy->e.right, enemy->e.bottom, GetColor(0, 255, 0), false);
	}
	 //当たり判定(エネミーとプレイヤー）
	if (enemy != nullptr) {
		if (hit->Hit(player->p, enemy->e) == true) {
			if (player->GetDamageFlag() == false) {
				player->SetDamageFlag(true);
				life--;
				player->Damage();
			}
			//デバッグ用
		/*	player->player->tmp.x = player->player->pos.x + 0.5f;
			player->SetPos(player->player->tmp);*/
			DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), true);
		}
	}
	//当たり判定上	
	if ((field->GetMapData(player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2) != 0) &&
		(player->GetPos().x + player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2) != 0) {
		player->SetHitTFlag(true);
		DrawBox(0, 0, 20, 20, GetColor(0,255, 0), true);
	}
	else {		//当たっていないときの処理
		player->SetHitTFlag(false);
	}
	//当たり判定下(マップとプレイヤー)
	if ((field->GetMapData(player->GetPos().x - player->GetSize().x / 2, player->GetPos().y + player->GetSize().y / 2) != 0) &&
		(player->GetPos().x + player->GetSize().x / 2, player->GetPos().y + player->GetSize().y / 2) != 0) {
		player->SetHitBFlag(true);
		DrawBox(0, 0, 20, 20, GetColor(0, 0, 255), true);
	}
	else {		//当たっていないときの処理
		player->SetHitBFlag(false);
	}
	
	
	LifeRender();//プレイヤーのライフを描画

	//デバッグ用
	//フラグ状態の表示
	if (player != nullptr) {
		DrawFormatString(300, 0, 0xffffff, "walkFlag % d", player->GetWalkFlag());
		DrawFormatString(300, 20, 0xffffff, "jumpFlag % d", player->GetJumpFlag());
		DrawFormatString(300, 40, 0xffffff, "brakeFlag % d", player->GetBrakeFlag());
		DrawFormatString(300, 60, 0xffffff, "damageFlag % d", player->GetDamageFlag());
		DrawFormatString(300, 100, 0xffffff, "hitTFlag % d", player->GetHitTFlag());
		DrawFormatString(300, 120, 0xffffff, "hitBFlag % d", player->GetHitBFlag());
		DrawFormatString(300, 140, 0xffffff, "LRFlag % d", player->GetLRFlag());
		DrawFormatString(0, 20, 0xffffff, "posx %.2f", player->GetPos().x);
		DrawFormatString(0, 40, 0xffffff, "posy %.2f", player->GetPos().y);
		DrawFormatString(140, 20, 0xffffff, "movx %.2f", player->GetMov().x);
		DrawFormatString(140, 40, 0xffffff, "movy %.2f", player->GetMov().y);
	}
	//Cキーが押されたときエネミーを消す
	if (KeyMng::GetInstance().newKey[P1_C]) {
		delete enemy;
		enemy = nullptr;
	}
	//Dキーが押されたときにエネミーを生成
	if ((enemy == nullptr) && (KeyMng::GetInstance().newKey[P1_D])) {
		enemy = new Enemy();
	}
	//Xキーが押されたときにエネミーのフラグをtrue
	if ((enemy != nullptr) && (KeyMng::GetInstance().newKey[P1_X])) {
		enemy->SetDeadFlag(true);
	}

	DrawString(0, 0, "main", GetColor(255, 255, 255));
	return 0;
}

int GameTask::GameOver(void)
{
	DrawString(0, 0, "over", GetColor(255, 255, 255));
	return 0;
}

int GameTask::GameClear(void)
{
	if (enemy != nullptr) {
		delete enemy;
		enemy = nullptr;
	}
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}

	DrawString(0, 0, "clear", GetColor(255, 255, 255));
	return 0;
}


void GameTask::LifeRender(void)
{
	int xpos = 110, ypos = 70;	//画像表示するX座標値、Y座標値
	int xposShif = 20;			//X座標をずらす値

	if (life >= 2) {
		ImageMng::GetInstance().DrawImage("life", xpos, ypos, true, 1);
		ImageMng::GetInstance().DrawImage("life", xpos + xposShif, ypos, true, 1);
	}
	if (life >= 1) {
		ImageMng::GetInstance().DrawImage("life", xpos, ypos, true, 1);
	}
}
