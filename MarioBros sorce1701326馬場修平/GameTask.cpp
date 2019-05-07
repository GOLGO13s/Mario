#include "DxLib.h"
#include "GameTask.h"
#include "KeyMng.h"
#include "ImageMng.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "HitCheck.h"

//スクリーンのサイズ
int GameTask::SCREEN_SIZE_X = 512;
int GameTask::SCREEN_SIZE_Y = 512;
int offset_y = 300;

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
		if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_DESCRIPTION;
		break;
	case GAME_DESCRIPTION:
		GameDescription();
		if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_MAIN;
		break;
	case GAME_MAIN:
		GameMain();
		if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_OVER;
		break;
	case GAME_OVER:
		GameOver();
		if (KeyMng::GetInstance().trgKey[P1_ENTER])gameMode = GAME_INIT;
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
	if (field != nullptr) {
		delete field;
		field = nullptr;
	}
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}
	std::list<Enemy*>::iterator ditr = EnemyList.begin();
	while (ditr != EnemyList.end())
	{
		delete (*ditr);//実体を消す
		ditr = EnemyList.erase(ditr);
	}
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
	//コインクラスのインスタンス化
	if (coin == nullptr)coin = new Coin();
	//ヒットクラスのインスタンス化
	if (hit == nullptr)hit = new HitCheck();
	//画像読み込み
	ImageMng::GetInstance().SetID("title", "image/title2.png");
	ImageMng::GetInstance().SetID("life", "image/life2.png");
	//初期化
	life = 2;	//プレイヤーのライフ
	ecount = 0;	//エネミーのカウント
	score = 0;	//スコア
	//フォントハンドル(スコアの描画に使用）
	Font = CreateFontToHandle("ALGERIAN", 25, 3, DX_FONTTYPE_ANTIALIASING);
	return 0;
}

//タイトル画面
int GameTask::GameTitle(void)
{
	int title_X = 0,title_Y = 0;
	ImageMng::GetInstance().DrawImage("title",title_X, title_Y, true, 1);
	DrawStringToHandle(120, 350, "START Key ENTER", 0x00ffff,Font);
	return 0;
}

int GameTask::GameDescription(void)
{
	DrawString(150, 0, "操作方法", 0xffff00);
	DrawString(150, 20, "←キー 左移動", 0xffff00);
	DrawString(150, 40, "→キー 右移動", 0xffff00);
	DrawString(150, 60, "SPACEキー ジャンプ", 0xffff00);
	DrawString(30, 100, "敵(亀)の倒し方", 0xff00ff);
	DrawString(30, 120, "ジャンプで敵に当たることで瀕死状態に出来る", 0xff00ff);
	DrawString(30, 140, "敵が瀕死状態の時もう一度当たると倒せる", 0xff00ff);
	DrawString(30, 160, "敵が通常状態の時に当たるとプレイヤーのライフが減る", 0xff00ff);
	DrawString(30, 180, "敵は一定時間で瀕死状態から復活する", 0xff00ff);
	DrawStringToHandle(70, 300, "START GAME Key ENTER", 0x00ffff, Font);
	DrawStringToHandle(60, 380, "SHUTDOWN GAME Key Esc", 0x00f00f, Font);
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
	//エネミー生成
	ecount++;
	if (1 >= ecount) {
		Enemy*e = new Enemy();
		EnemyList.push_back(e);
	}
	//エネミーの更新と描画
	std::list<Enemy*>::iterator itr;
	for (itr = EnemyList.begin(); itr != EnemyList.end(); ++itr)
	{
		(*itr)->Update();
		(*itr)->Draw();
		//エネミーとマップの当たり判定
		EnemyVSMap((*itr)->GetPos().x, (*itr)->GetPos().y, (*itr)->GetSize().x, (*itr)->GetSize().y);
		//エネミーが死んだときの座標をコインの座標にセットして描画する
		if ((*itr)->GetDeathFlag() == true) {
			coin->SetPos((*itr)->GetPos());
			coin->Draw();
		}
	}
	//プレイヤーとエネミーの当たり判定
	PlayerVSEnemy();		
	//プレイヤーとコインの当たり判定
	PlayerVSCoin();
	//プレイヤーとマップの当たり判定	
	PlayerVSMap(player->GetPos().x, player->GetPos().y, player->GetSize().x, player->GetSize().y);
	//プレイヤーとPowブロックの当たり判定
	PlayerVSPow(player->GetPos().x, player->GetPos().y, player->GetSize().x, player->GetSize().y);
	
	if (life == 0) {
		gameMode = GAME_OVER;
	}
	LifeRender();//プレイヤーのライフを描画

	if (KeyMng::GetInstance().newKey[P1_C]) {
		std::list<Enemy*>::iterator ditr = EnemyList.begin();
		while (ditr != EnemyList.end())
		{
			delete (*ditr);//実体を消す
			ditr = EnemyList.erase(ditr);
			ecount = 0;
		}
	}

	//スコアの描画
	DrawFormatStringToHandle(200, 25, 0xffffff, Font, "SCORE % d", score);
	//デバッグ用
	//フラグ状態の表示
	/*DrawFormatString(300, 0, 0xffffff, "walkFlag % d", player->GetWalkFlag());
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
	DrawFormatStringToHandle(150, 10, 0xffffff, Font, "SCORE %d", score);
	DrawFormatString(300, 40, 0xffffff, "jumpFlag % d", player->GetJumpFlag());
	DrawString(0, 0, "main", GetColor(255, 255, 255));*/
	return 0;
}

int GameTask::GameOver(void)
{
	//エネミー削除
	std::list<Enemy*>::iterator ditr = EnemyList.begin();
	while (ditr != EnemyList.end())
	{
		delete (*ditr);//実体を消す
		ditr = EnemyList.erase(ditr);
	}
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}
	int x_offset = 160;
	int y_offset = 150;
	DrawStringToHandle(x_offset, y_offset, "Game Over", 0xffffff, Font);
	DrawStringToHandle(x_offset - 60, y_offset + 100, "Continue Key Enter", 0x00ffff, Font);
	DrawStringToHandle(x_offset - 90, y_offset + 200, "SHUTDOWN GAME Key Esc", 0x00f00f, Font);
	return 0;
}

void GameTask::PlayerVSEnemy()
{
	// 当たり判定用のデータの準備
	//プレイヤーのRECTを再設定
	if (player != nullptr) {
		int p_width = player->p.right - player->p.left;
		int p_height = player->p.bottom - player->p.top;
		SetRect(&player->p, player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2,
			player->GetPos().x + p_width / 2, player->GetPos().y + p_height / 2);
		//RECTの範囲を描画
		//DrawBox(player->p.left, player->p.top, player->p.right, player->p.bottom, GetColor(255, 0, 0), false);
	}
	//エネミ-
	std::list<Enemy*>::iterator itr;
	for (itr = EnemyList.begin(); itr != EnemyList.end(); ++itr)
	{
		//デバッグ用
		//DrawFormatString(0, 40, 0xffffff, "DyingFlag % d", (*itr)->GetDyingFlag());
		//エネミーのRECTを再設定
		if ((*itr) != nullptr) {
			int e_width = (*itr)->e.right - (*itr)->e.left;
			int e_height = (*itr)->e.bottom - (*itr)->e.top;
			SetRect(&(*itr)->e, (*itr)->GetPos().x - (*itr)->GetSize().x / 2, (*itr)->GetPos().y - (*itr)->GetSize().y / 2,
				(*itr)->GetPos().x + e_width / 2, (*itr)->GetPos().y + e_height / 2);
			//RECTの範囲を描画
			//DrawBox((*itr)->e.left, (*itr)->e.top, (*itr)->e.right, (*itr)->e.bottom, GetColor(0, 255, 0), false);
		}

		//プレイヤーがジャンプ中の時敵を瀕死状態にする
		if ((player->GetJumpFlag() == true) && (hit->Hit(player->p, (*itr)->e) == true)) {
			(*itr)->SetDyingFlag(true);
		}
		//通常はプレイヤーだけがダメージを受ける
		if (hit->Hit(player->p, (*itr)->e) == true){
			if ((*itr)->GetDyingFlag() == false) {
				if (player->GetDamageFlag() == false) {
					player->SetDamageFlag(true);
					life--; //プレイヤーのライフを減らす
				}
			}
			//敵が瀕死状態で再び当たると敵を消すフラグをtrueにする
			if (((*itr)->GetDyingFlag() == true)&&(player->GetJumpFlag() == false)) {
				(*itr)->SetDeathFlag(true);
				(*itr)->SetDyingFlag(false);
				score += 10;
			}
			//デバッグ用
			//DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), true);
		}
		else {//敵と当たっていない時
			player->SetDamageFlag(false); 
		}
		
	}
	//エネミーを削除
	std::list<Enemy*>::iterator ditr = EnemyList.begin();
	while (ditr != EnemyList.end())
	{
		if ((*ditr)->GetDeathFlag() == true)
		{
			delete (*ditr);//実体を消す
			ditr = EnemyList.erase(ditr);
			ecount = 0;
		}
		else {
			ditr++;
		}
	}
}

void GameTask::PlayerVSCoin()
{
	// 当たり判定用のデータの準備
	//プレイヤーのRECTを再設定
	if (player != nullptr) {
		int p_width = player->p.right - player->p.left;
		int p_height = player->p.bottom - player->p.top;
		SetRect(&player->p, player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2,
			player->GetPos().x + p_width / 2, player->GetPos().y + p_height / 2);
		//RECTの範囲を描画
		//DrawBox(player->p.left, player->p.top, player->p.right, player->p.bottom, GetColor(255, 0, 0), false);
	}
	//コイン
	//デバッグ用
	//コインのRECTを再設定
		int c_width = coin->c.right - coin->c.left;
		int c_height = coin->c.bottom - coin->c.top;
		SetRect(&coin->c, coin->GetPos().x - coin->GetSize().x / 2, coin->GetPos().y - coin->GetSize().y / 2,
			coin->GetPos().x + c_width / 2, coin->GetPos().y + c_height / 2);
		//RECTの範囲を描画
		//DrawBox(coin->c.left, coin->c.top, coin->c.right, coin->c.bottom, GetColor(0, 255, 0), false);
	//プレイヤーとコインが当たっていたらフラグをtrue
	if (hit->Hit(player->p, coin->c) == true) {
		if (coin->GetCoinFlag() == false) {
			coin->SetCoinFlag(true);
			score += 10;
		}
	}
	else {
		coin->SetCoinFlag(false);
	}
}



void GameTask::PlayerVSMap(float x, float y ,float sx , float sy)
{
	//当たり判定上(マップとプレイヤー)
	if ((field->GetMapData(x - sx / 2, y - sy / 2) != 0) && (x + sx / 2, y - sy / 2) != 0) {
		player->SetHitTFlag(true);
		if (player->GetHitTFlag() == true) {
			player->SetHitBFlag(false);

		}
		//DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), true);
	}
	else {		//当たっていないときの処理
		player->SetHitTFlag(false);
	}

	//当たり判定下(マップとプレイヤー)
	//左下と右下で判定
	if ((field->GetMapData(x - sx / 2, y + sy / 2) != 0)&& (x + sx / 2,y + sy / 2) != 0) {
		player->SetHitBFlag(true);
		//デバッグ用
		//DrawBox(0, 0, 20, 20, GetColor(0, 0, 255), true);
	}
	else {		//当たっていないときの処理
		player->SetHitBFlag(false);
	}
}

void GameTask::PlayerVSPow(float x, float y, float sx, float sy)
{
	//powブロックとの当たり判定
	if ((field->GetMapData(x - sx / 2, y - sy / 2) == 199) || (x + sx / 2, y - sy / 2) == 199 || 
		(field->GetMapData(x - sx / 2, y - sy / 2) == 200) || (x + sx / 2, y - sy / 2) == 200) {
		player->SetHitTFlag(true);
		//DrawBox(0, 0, 20, 20, GetColor(255, 255, 0), true);
	}
	else {
		player->SetHitTFlag(false);
	}
}

void GameTask::EnemyVSMap(float x, float y, float sx, float sy)
{
	std::list<Enemy*>::iterator itr;
	for (itr = EnemyList.begin(); itr != EnemyList.end(); ++itr)
	{
		if ((field->GetMapData(x - sx / 2, y + sy / 2) != 0) && (x + sx / 2, y + sy / 2) != 0) {
			(*itr)->SetEHitBFlag(true);
			//DrawBox(0, 0, 20, 20, GetColor(0, 0, 255), true);
		}
		else {		//当たっていないときの処理
			(*itr)->SetEHitBFlag(false);
		}
		//デバッグ用
	/*	DrawBox((*itr)->GetPos().x - (*itr)->GetSize().x / 2,
			(*itr)->GetPos().y + (*itr)->GetSize().y / 2,
			(*itr)->GetPos().x + (*itr)->GetSize().x / 2,
			(*itr)->GetPos().y + (*itr)->GetSize().y / 2, GetColor(255, 0, 0), false);*/
	}
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




