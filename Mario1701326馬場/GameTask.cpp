#include "DxLib.h"
#include "GameTask.h"
#include "KeyMng.h"
#include "ImageMng.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "HitCheck.h"

//�X�N���[���̃T�C�Y
int GameTask::SCREEN_SIZE_X = 512;
int GameTask::SCREEN_SIZE_Y = 512;

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
	//�G�l�~�[�N���X�Ƀ��X�^���X��
	if (enemy == nullptr)enemy = new Enemy();
	if (hit == nullptr)hit = new HitCheck();
	//�摜�ǂݍ���
	ImageMng::GetInstance().SetID("title", "image/title.png");
	ImageMng::GetInstance().SetID("life", "image/life2.png");
	//������
	life = 2;
	return 0;
}

//�^�C�g�����
int GameTask::GameTitle(void)
{
	int title_X = 0,title_Y = 0;
	ImageMng::GetInstance().DrawImage("title",title_X, title_Y, true, 1);
	DrawString(200, 480, "START ENTER", GetColor(255, 255, 255));
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
	if (enemy != nullptr) {
		enemy->Update();
		enemy->Draw();
	}

	// �f�[�^�̏���
	//�L�����N�^�摜�̋�`�Ƃ��C�����W�����ɍ���E�����W�f�[�^���쐬���A�����蔻��ɗ��p����B
	//�v���C���[
	if (player != nullptr) {
		int p_width = player->p.right - player->p.left;
		int p_height = player->p.bottom - player->p.top;
		SetRect(&player->p, player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2,
			player->GetPos().x + p_width / 2, player->GetPos().y + p_height / 2);
		//RECT�͈̔͂�`��
		DrawBox(player->p.left, player->p.top, player->p.right, player->p.bottom, GetColor(255, 0, 0), false);
	}
	//�G�l�~�[
	if (enemy != nullptr) {
		int e_width = enemy->e.right - enemy->e.left;
		int e_height = enemy->e.bottom - enemy->e.top;
		SetRect(&enemy->e, enemy->GetPos().x - enemy->GetSize().x / 2, enemy->GetPos().y - enemy->GetSize().y / 2,
			enemy->GetPos().x + e_width / 2, enemy->GetPos().y + e_height / 2);
		//RECT�͈̔͂�`��
		DrawBox(enemy->e.left, enemy->e.top, enemy->e.right, enemy->e.bottom, GetColor(0, 255, 0), false);
	}
	 //�����蔻��(�G�l�~�[�ƃv���C���[�j
	if (enemy != nullptr) {
		if (hit->Hit(player->p, enemy->e) == true) {
			if (player->GetDamageFlag() == false) {
				player->SetDamageFlag(true);
				life--;
				player->Damage();
			}
			//�f�o�b�O�p
		/*	player->player->tmp.x = player->player->pos.x + 0.5f;
			player->SetPos(player->player->tmp);*/
			DrawBox(0, 0, 20, 20, GetColor(255, 0, 0), true);
		}
	}
	//�����蔻���	
	if ((field->GetMapData(player->GetPos().x - player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2) != 0) &&
		(player->GetPos().x + player->GetSize().x / 2, player->GetPos().y - player->GetSize().y / 2) != 0) {
		player->SetHitTFlag(true);
		DrawBox(0, 0, 20, 20, GetColor(0,255, 0), true);
	}
	else {		//�������Ă��Ȃ��Ƃ��̏���
		player->SetHitTFlag(false);
	}
	//�����蔻�艺(�}�b�v�ƃv���C���[)
	if ((field->GetMapData(player->GetPos().x - player->GetSize().x / 2, player->GetPos().y + player->GetSize().y / 2) != 0) &&
		(player->GetPos().x + player->GetSize().x / 2, player->GetPos().y + player->GetSize().y / 2) != 0) {
		player->SetHitBFlag(true);
		DrawBox(0, 0, 20, 20, GetColor(0, 0, 255), true);
	}
	else {		//�������Ă��Ȃ��Ƃ��̏���
		player->SetHitBFlag(false);
	}
	
	
	LifeRender();//�v���C���[�̃��C�t��`��

	//�f�o�b�O�p
	//�t���O��Ԃ̕\��
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
	//C�L�[�������ꂽ�Ƃ��G�l�~�[������
	if (KeyMng::GetInstance().newKey[P1_C]) {
		delete enemy;
		enemy = nullptr;
	}
	//D�L�[�������ꂽ�Ƃ��ɃG�l�~�[�𐶐�
	if ((enemy == nullptr) && (KeyMng::GetInstance().newKey[P1_D])) {
		enemy = new Enemy();
	}
	//X�L�[�������ꂽ�Ƃ��ɃG�l�~�[�̃t���O��true
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
