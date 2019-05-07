#include "DxLib.h"
#include "GameTask.h"
#include "KeyMng.h"
#include "ImageMng.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "HitCheck.h"

//�X�N���[���̃T�C�Y
int GameTask::SCREEN_SIZE_X = 512;
int GameTask::SCREEN_SIZE_Y = 512;
int offset_y = 300;

int GameTask::GameUpDate(void)
{
	//�L�[���X�V
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

//�R���X�g���N�^
GameTask::GameTask()
{
	SystemInit();
	gameMode = GAME_INIT;
	oldKey = 0;
}

//�f�X�g���N�^
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
		delete (*ditr);//���̂�����
		ditr = EnemyList.erase(ditr);
	}
}

//-----�V�X�e��������
int GameTask::SystemInit(void)
{
	SetWindowText("�}���I�u���U�[�Y 1701326�n��C��");
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
	//�t�B�[���h�̃N���X�̃C���X�^���X
	if (field == nullptr)field = new Field();
	//�v���C���[�N���X�̃C���X�^���X
	if (player == nullptr)player = new Player();
	//�R�C���N���X�̃C���X�^���X��
	if (coin == nullptr)coin = new Coin();
	//�q�b�g�N���X�̃C���X�^���X��
	if (hit == nullptr)hit = new HitCheck();
	//�摜�ǂݍ���
	ImageMng::GetInstance().SetID("title", "image/title2.png");
	ImageMng::GetInstance().SetID("life", "image/life2.png");
	//������
	life = 2;	//�v���C���[�̃��C�t
	ecount = 0;	//�G�l�~�[�̃J�E���g
	score = 0;	//�X�R�A
	//�t�H���g�n���h��(�X�R�A�̕`��Ɏg�p�j
	Font = CreateFontToHandle("ALGERIAN", 25, 3, DX_FONTTYPE_ANTIALIASING);
	return 0;
}

//�^�C�g�����
int GameTask::GameTitle(void)
{
	int title_X = 0,title_Y = 0;
	ImageMng::GetInstance().DrawImage("title",title_X, title_Y, true, 1);
	DrawStringToHandle(120, 350, "START Key ENTER", 0x00ffff,Font);
	return 0;
}

int GameTask::GameDescription(void)
{
	DrawString(150, 0, "������@", 0xffff00);
	DrawString(150, 20, "���L�[ ���ړ�", 0xffff00);
	DrawString(150, 40, "���L�[ �E�ړ�", 0xffff00);
	DrawString(150, 60, "SPACE�L�[ �W�����v", 0xffff00);
	DrawString(30, 100, "�G(�T)�̓|����", 0xff00ff);
	DrawString(30, 120, "�W�����v�œG�ɓ����邱�Ƃŕm����Ԃɏo����", 0xff00ff);
	DrawString(30, 140, "�G���m����Ԃ̎�������x������Ɠ|����", 0xff00ff);
	DrawString(30, 160, "�G���ʏ��Ԃ̎��ɓ�����ƃv���C���[�̃��C�t������", 0xff00ff);
	DrawString(30, 180, "�G�͈�莞�Ԃŕm����Ԃ��畜������", 0xff00ff);
	DrawStringToHandle(70, 300, "START GAME Key ENTER", 0x00ffff, Font);
	DrawStringToHandle(60, 380, "SHUTDOWN GAME Key Esc", 0x00f00f, Font);
	return 0;
}

//-----�Q�[�����
int GameTask::GameMain(void)
{
	//�t�B�[���h�̕`��
	if (field != nullptr) {
		field->Draw();
	}
	
	//�v���C���[�̍X�V
	if (player != nullptr) {
		player->Update();
		player->Draw();
	}
	//�G�l�~�[�̍X�V�ƕ`��
	//�G�l�~�[����
	ecount++;
	if (1 >= ecount) {
		Enemy*e = new Enemy();
		EnemyList.push_back(e);
	}
	//�G�l�~�[�̍X�V�ƕ`��
	std::list<Enemy*>::iterator itr;
	for (itr = EnemyList.begin(); itr != EnemyList.end(); ++itr)
	{
		(*itr)->Update();
		(*itr)->Draw();
		//�G�l�~�[�ƃ}�b�v�̓����蔻��
		EnemyVSMap((*itr)->GetPos().x, (*itr)->GetPos().y, (*itr)->GetSize().x, (*itr)->GetSize().y);
		//�G�l�~�[�����񂾂Ƃ��̍��W���R�C���̍��W�ɃZ�b�g���ĕ`�悷��
		if ((*itr)->GetDeathFlag() == true) {
			coin->SetPos((*itr)->GetPos());
			coin->Draw();
		}
	}
	//�v���C���[�ƃG�l�~�[�̓����蔻��
	PlayerVSEnemy();		
	//�v���C���[�ƃR�C���̓����蔻��
	PlayerVSCoin();
	//�v���C���[�ƃ}�b�v�̓����蔻��	
	PlayerVSMap(player->GetPos().x, player->GetPos().y, player->GetSize().x, player->GetSize().y);
	//�v���C���[��Pow�u���b�N�̓����蔻��
	PlayerVSPow(player->GetPos().x, player->GetPos().y, player->GetSize().x, player->GetSize().y);
	
	if (life == 0) {
		gameMode = GAME_OVER;
	}
	LifeRender();//�v���C���[�̃��C�t��`��

	if (KeyMng::GetInstance().newKey[P1_C]) {
		std::list<Enemy*>::iterator ditr = EnemyList.begin();
		while (ditr != EnemyList.end())
		{
			delete (*ditr);//���̂�����
			ditr = EnemyList.erase(ditr);
			ecount = 0;
		}
	}

	//�X�R�A�̕`��
	DrawFormatStringToHandle(200, 25, 0xffffff, Font, "SCORE % d", score);
	//�f�o�b�O�p
	//�t���O��Ԃ̕\��
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
	//�G�l�~�[�폜
	std::list<Enemy*>::iterator ditr = EnemyList.begin();
	while (ditr != EnemyList.end())
	{
		delete (*ditr);//���̂�����
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
	// �����蔻��p�̃f�[�^�̏���
	//�v���C���[��RECT���Đݒ�
	if (player != nullptr) {
		int p_width = player->p.right - player->p.left;
		int p_height = player->p.bottom - player->p.top;
		SetRect(&player->p, player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2,
			player->GetPos().x + p_width / 2, player->GetPos().y + p_height / 2);
		//RECT�͈̔͂�`��
		//DrawBox(player->p.left, player->p.top, player->p.right, player->p.bottom, GetColor(255, 0, 0), false);
	}
	//�G�l�~-
	std::list<Enemy*>::iterator itr;
	for (itr = EnemyList.begin(); itr != EnemyList.end(); ++itr)
	{
		//�f�o�b�O�p
		//DrawFormatString(0, 40, 0xffffff, "DyingFlag % d", (*itr)->GetDyingFlag());
		//�G�l�~�[��RECT���Đݒ�
		if ((*itr) != nullptr) {
			int e_width = (*itr)->e.right - (*itr)->e.left;
			int e_height = (*itr)->e.bottom - (*itr)->e.top;
			SetRect(&(*itr)->e, (*itr)->GetPos().x - (*itr)->GetSize().x / 2, (*itr)->GetPos().y - (*itr)->GetSize().y / 2,
				(*itr)->GetPos().x + e_width / 2, (*itr)->GetPos().y + e_height / 2);
			//RECT�͈̔͂�`��
			//DrawBox((*itr)->e.left, (*itr)->e.top, (*itr)->e.right, (*itr)->e.bottom, GetColor(0, 255, 0), false);
		}

		//�v���C���[���W�����v���̎��G��m����Ԃɂ���
		if ((player->GetJumpFlag() == true) && (hit->Hit(player->p, (*itr)->e) == true)) {
			(*itr)->SetDyingFlag(true);
		}
		//�ʏ�̓v���C���[�������_���[�W���󂯂�
		if (hit->Hit(player->p, (*itr)->e) == true){
			if ((*itr)->GetDyingFlag() == false) {
				if (player->GetDamageFlag() == false) {
					player->SetDamageFlag(true);
					life--; //�v���C���[�̃��C�t�����炷
				}
			}
			//�G���m����ԂōĂѓ�����ƓG�������t���O��true�ɂ���
			if (((*itr)->GetDyingFlag() == true)&&(player->GetJumpFlag() == false)) {
				(*itr)->SetDeathFlag(true);
				(*itr)->SetDyingFlag(false);
				score += 10;
			}
			//�f�o�b�O�p
			//DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), true);
		}
		else {//�G�Ɠ������Ă��Ȃ���
			player->SetDamageFlag(false); 
		}
		
	}
	//�G�l�~�[���폜
	std::list<Enemy*>::iterator ditr = EnemyList.begin();
	while (ditr != EnemyList.end())
	{
		if ((*ditr)->GetDeathFlag() == true)
		{
			delete (*ditr);//���̂�����
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
	// �����蔻��p�̃f�[�^�̏���
	//�v���C���[��RECT���Đݒ�
	if (player != nullptr) {
		int p_width = player->p.right - player->p.left;
		int p_height = player->p.bottom - player->p.top;
		SetRect(&player->p, player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2,
			player->GetPos().x + p_width / 2, player->GetPos().y + p_height / 2);
		//RECT�͈̔͂�`��
		//DrawBox(player->p.left, player->p.top, player->p.right, player->p.bottom, GetColor(255, 0, 0), false);
	}
	//�R�C��
	//�f�o�b�O�p
	//�R�C����RECT���Đݒ�
		int c_width = coin->c.right - coin->c.left;
		int c_height = coin->c.bottom - coin->c.top;
		SetRect(&coin->c, coin->GetPos().x - coin->GetSize().x / 2, coin->GetPos().y - coin->GetSize().y / 2,
			coin->GetPos().x + c_width / 2, coin->GetPos().y + c_height / 2);
		//RECT�͈̔͂�`��
		//DrawBox(coin->c.left, coin->c.top, coin->c.right, coin->c.bottom, GetColor(0, 255, 0), false);
	//�v���C���[�ƃR�C�����������Ă�����t���O��true
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
	//�����蔻���(�}�b�v�ƃv���C���[)
	if ((field->GetMapData(x - sx / 2, y - sy / 2) != 0) && (x + sx / 2, y - sy / 2) != 0) {
		player->SetHitTFlag(true);
		if (player->GetHitTFlag() == true) {
			player->SetHitBFlag(false);

		}
		//DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), true);
	}
	else {		//�������Ă��Ȃ��Ƃ��̏���
		player->SetHitTFlag(false);
	}

	//�����蔻�艺(�}�b�v�ƃv���C���[)
	//�����ƉE���Ŕ���
	if ((field->GetMapData(x - sx / 2, y + sy / 2) != 0)&& (x + sx / 2,y + sy / 2) != 0) {
		player->SetHitBFlag(true);
		//�f�o�b�O�p
		//DrawBox(0, 0, 20, 20, GetColor(0, 0, 255), true);
	}
	else {		//�������Ă��Ȃ��Ƃ��̏���
		player->SetHitBFlag(false);
	}
}

void GameTask::PlayerVSPow(float x, float y, float sx, float sy)
{
	//pow�u���b�N�Ƃ̓����蔻��
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
		else {		//�������Ă��Ȃ��Ƃ��̏���
			(*itr)->SetEHitBFlag(false);
		}
		//�f�o�b�O�p
	/*	DrawBox((*itr)->GetPos().x - (*itr)->GetSize().x / 2,
			(*itr)->GetPos().y + (*itr)->GetSize().y / 2,
			(*itr)->GetPos().x + (*itr)->GetSize().x / 2,
			(*itr)->GetPos().y + (*itr)->GetSize().y / 2, GetColor(255, 0, 0), false);*/
	}
}


void GameTask::LifeRender(void)
{
	int xpos = 110, ypos = 70;	//�摜�\������X���W�l�AY���W�l
	int xposShif = 20;			//X���W�����炷�l

	if (life >= 2) {
		ImageMng::GetInstance().DrawImage("life", xpos, ypos, true, 1);
		ImageMng::GetInstance().DrawImage("life", xpos + xposShif, ypos, true, 1);
	}
	if (life >= 1) {
		ImageMng::GetInstance().DrawImage("life", xpos, ypos, true, 1);
	}
}




