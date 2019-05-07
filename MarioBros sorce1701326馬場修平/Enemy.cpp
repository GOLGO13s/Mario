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
	//�G�l�~�[�摜�ǂݍ���
	//enemy(�T)
	VECTOR2 divSize = { 29,32 };
	VECTOR2 divNum = { 3,1 };
	VECTOR2 coindivNum = { 10,1 };
	ImageMng::GetInstance().SetID("turtle", "image/enemy.png", divSize, divNum);
	ImageMng::GetInstance().SetID("turtle dying", "image/dying.png", divSize, divNum);
}

void Enemy::Init()
{
	//������
	pos.x = (0.0f);
	pos.y = (150.0f);
	size = { 29 ,32 };
	//RECT
	e.top = pos.y - size.y/2;
	e.bottom = pos.y + size.y/2;
	e.left = pos.x - size.x/2;
	e.right = pos.x + size.x / 2;
	G = 3.0f;		//�d��
	speed = 2.0f;
	int Parme = GetRand(1);
	if(Parme == 0)lrFlag = false;		//false�E����,ture;������
	if(Parme == 1)lrFlag = true;
	dyingFlag = false;	//true�łЂ�����Ԃ���(�m�����)�ɂ���
	deathFlag = false;	//true�Ŏ��S��Ԃɂ���
	movFlag = true;
	animCnt = 0;
	revivalCnt = 0;
}

void Enemy::Update()
{
	
	if (pos.x + size.x / 2 <= StartPos) {

		pos.x = EndPos;
	}
	if (pos.x - size.x / 2 >= EndPos) {
		pos.x = StartPos;
	}

	if (movFlag == true) {
		if (lrFlag == true) {
			pos.x -= speed;
		}
		else {
			pos.x += speed;
		}
	}

	if (dyingFlag == true) {
		speed = 0.0f;
	}

	//�n�ʂɓ������Ă��Ȃ����̏���
	if (ehitBFlag == false) {
		pos.y = pos.y + G;
		movFlag = false;
	}
	//�n�ʂɓ����������̏���
	if (ehitBFlag == true) {
		movFlag = true;
	}
	if (dyingFlag == true) {
		revivalCnt++;
	}
	if (revivalCnt > 180) {
		dyingFlag = false;
	}
	if (dyingFlag == false) {
		revivalCnt = 0;
		speed = 2.0f;
	}
}

void Enemy::Draw()
{
	animCnt++;
	//�A�j���[�V�����`��
	if (dyingFlag == false){
		ImageMng::GetInstance().DrawImage("turtle", pos.x - size.x / 2, pos.y - size.y / 2, animCnt / 7 % 3 == 0, true, lrFlag);
	}
	if (dyingFlag == true){
		ImageMng::GetInstance().DrawImage("turtle dying", pos.x - size.x / 2, pos.y - size.y / 2, animCnt / 7 % 3 == 0, true, lrFlag);
	}
}


