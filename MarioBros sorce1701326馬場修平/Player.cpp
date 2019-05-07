#include"DxLib.h"
#include "Chara_Base.h"
#include"ImageMng.h"
#include "KeyMng.h"
#include "Player.h"
#include "Field.h"

constexpr float speed = 1.5f;				//ウォークモーション時スピード
constexpr float runspeed = 4.5f;			//ダッシュモーション時スピード
constexpr float RSPEED_MAX = 1.5;			//ウォークスピード最大値
constexpr float LSPEED_MAX = -1.5f;			//ウォークスピード最大値
constexpr float RUN_RSPEED_MAX = 4.5f;		//ダッシュスピード最大値
constexpr float RUN_LSPEED_MAX = -4.5f;		//ダッシュスピード最大値

Player::Player()
{
	SystemInit();
	Init();
}

Player::~Player()
{

}

void Player::SystemInit()
{
	//画像登録
	//静止画像
	ImageMng::GetInstance().SetID("stop2", "image/stop.png");
	//動き（歩き&走り)画像
	VECTOR2 divSize = { 32,45 };
	VECTOR2 divNum = { 2,1 };
	ImageMng::GetInstance().SetID("move", "image/move.png", divSize, divNum);
	//ジャンプ画像
	VECTOR2 jdivSize = { 32,45 };
	VECTOR2 jdivNum = { 2,1 };
	ImageMng::GetInstance().SetID("jump", "image/jump.png", jdivSize, jdivNum);
	//ブレーキ画像
	VECTOR2 bdivSize = {32,45 };
	VECTOR2 bdivNum = { 2,1 };
	ImageMng::GetInstance().SetID("brake", "image/brake.png", bdivSize, bdivNum);
	//ダメージ画像
	VECTOR2 ddivSize = { 32,45 };
	VECTOR2 ddivNum = { 3,1 };
	ImageMng::GetInstance().SetID("damage","image/damage.png",ddivSize,ddivNum);

}

void Player::Init()
{
	//パラメータ初期化
	animCnt = 0;						//アニメーション用カウント
	player.pos = { 250.0f,449.0f };		//プレイヤーの座標
	player.mov = { 0.0f,0.0f };			//プレイヤーの移動値
	player.tmp = { 0.0f,0.0f };			//プレイヤーの値を一時的に持つ変数
	jumppow = 0.0f;						//ジャンプパワー
	pow = 15.0f;						//ジャンプパワー
	G = 0.98f;							//落下時の重力
	player.size = { 32,45 };			//プレイヤーの画像サイズ(立ち絵と動きモーション)
	player.bsize = { 32,45 };			//プレイヤーの画像サイズ(ブレーキモーション)
	player.jsize = { 32,45 };			//プレイヤーの画像サイズ(ジャンプモーション)
	player.dsize = { 32,45 };			//プレイヤーの画像サイズ(ダメージモーション)

	//フラグ初期化
	player.walkFlag = false;			//false:ウォークしていない,ture;ウォーク中
	player.lrFlag = false;				//false右向き,ture;左向き
	player.jumpFlag = false;			//false:ジャンプしていない,ture;ジャンプ中
	player.brakeFlag = false;			//false:非ブレーキ状態,ture;ブレーキ状態
	player.damageFlag = false;			//false:ダメージを食らっていない,true:ダメージを食らった
	player.hitTFlag = false;			//false:当たっている,true:当たっていない
	player.hitBFlag = false;			//false:当たっている,true:当たっていない

	//RECT
	p.left = player.pos.x - player.size.x / 2;
	p.right = player.pos.x + player.size.x / 2;
	p.top = player.pos.y - player.size.y / 2;
	p.bottom = player.pos.y + player.size.y / 2;
}

void Player::Update()
{
	player.walkFlag = false;
	player.brakeFlag = false;

	//ウォーク処理
	if (KeyMng::GetInstance().newKey[P1_RIGHT]) {
		if (player.mov.x < RSPEED_MAX) {
			player.mov.x += speed;
		}
		player.walkFlag = true;
		player.lrFlag = false;
		player.brakeFlag = false;
		if (player.pos.x - player.size.x / 2 >= EndPos) {
			player.pos.x = StartPos;
		}
	}
	if (KeyMng::GetInstance().newKey[P1_LEFT]) {
		if (player.mov.x > LSPEED_MAX) {
			player.mov.x -= speed;
		}
		player.walkFlag=true;
		player.lrFlag = true;
		player.brakeFlag = false;
		if (player.pos.x + player.size.x / 2 <= StartPos) {
			player.pos.x = EndPos;
		}
	}
	//ダッシュ処理
	if ((KeyMng::GetInstance().newKey[P1_RIGHT]) && (KeyMng::GetInstance().newKey[P1_LSHIFT])) {
		if (player.mov.x < RUN_RSPEED_MAX) {
			player.mov.x += speed;
		}
		player.lrFlag = false;
		player.brakeFlag = false;
	}
	if ((KeyMng::GetInstance().newKey[P1_LEFT]) && (KeyMng::GetInstance().newKey[P1_LSHIFT])) {
		if (player.mov.x > RUN_LSPEED_MAX) {
			player.mov.x -= speed;
		}     
		player.lrFlag = true;
		player.brakeFlag = false;
	}
	//ジャンプ処理
	if ((KeyMng::GetInstance().newKey[P1_SPACE]) && player.jumpFlag == false) {
		player.jumpFlag = true;
		player.hitBFlag = false;
		jumppow += pow;
	}
	if ((player.jumpFlag == true)||(player.hitBFlag == false)) {
		// 落下加速度を加える
		jumppow -= G;
		// 落下処理
		player.pos.y -= jumppow;
	}

	// もし地面についていたら止まる
	if ((player.jumpFlag == true)&&(player.hitBFlag == true)) {
		HitMapBottom();
		player.jumpFlag = false;
		jumppow = 0.0f;
	}

	//減速処理
	if ((player.walkFlag == false)&&(player.mov.x < -0.01f)) {
		player.mov.x += 0.1f;
		player.brakeFlag = true;
	}
	if ((player.walkFlag == false)&&(player.mov.x > 0.01f)) {
		player.mov.x -= 0.1f;
		player.brakeFlag = true;
	}

	//値を一時的に代入
	player.tmp.x = player.pos.x + player.mov.x;
	player.tmp.y = player.pos.y + player.mov.y;
		
	//最終的な座標
	player.pos.x = player.tmp.x;
	player.pos.y = player.tmp.y;
}

void Player::Draw()
{
	animCnt++;
	//静止モーション
	if ((player.walkFlag == false) && (player.jumpFlag == false) && (player.brakeFlag == false)) {
		ImageMng::GetInstance().DrawImage("stop2", player.pos.x - player.size.x / 2,
			player.pos.y - player.size.y / 2, true, player.lrFlag);
	}
	//ウォークモーション
	if ((player.walkFlag == true) && (player.jumpFlag == false) && (player.brakeFlag == false)) {
		ImageMng::GetInstance().DrawImage("move", player.pos.x - player.size.x / 2,
			player.pos.y - player.size.y / 2, animCnt / 7 % 4 == 0, true, player.lrFlag);
	}
	//ジャンプモーション
	if (player.jumpFlag == true) {
		ImageMng::GetInstance().DrawImage("jump", player.pos.x - player.jsize.x / 2,
			player.pos.y - player.jsize.y / 2, animCnt / 7 % 14 == 0, true, player.lrFlag);
	}
	////ブレーキモーション
	if (player.brakeFlag == true) {
		ImageMng::GetInstance().DrawImage("brake", player.pos.x - player.bsize.x / 2,
			player.pos.y - player.bsize.y / 2, animCnt / 7 % 2 == 0, true, player.lrFlag);
	}
	//ダメージモーション
	if (player.damageFlag == true) {
		ImageMng::GetInstance().DrawImage("damage", player.pos.x - player.dsize.x / 2,
			player.pos.y - player.dsize.y / 2, animCnt / 7 % 7 == 0, true, player.lrFlag);
	}
}

void Player::HitMapTop()
{
	if (player.hitTFlag == true) {
		player.tmp.y = player.pos.y + player.size.y/2 ;

	}
}

void Player::HitMapBottom()
{
	if (player.hitBFlag == true) {
		player.tmp.y = player.pos.y - player.size.y/2;
	}
}



