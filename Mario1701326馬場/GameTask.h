#pragma once

class Field;
class Player;
class Enemy;
class HitCheck;

//��ʑJ�ڗp
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
	GameTask(); //�R���X�g���N�^(�V���O���g��))
	GameTask(const GameTask&) {}		//�R�s�[�R���X�g���N�^��private��
	GameTask operator=(const GameTask&) {}	//�����private��
	~GameTask();//�f�X�g���N�^
public:
	static GameTask&GetInstance() {
		static GameTask gInst;
		return gInst;
	}
	int SystemInit(void);	//�V�X�e��������
	int GameUpDate(void);	//�Q�[�����[�v���C��

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
	Field*field;	//�t�B�[���h�̃I�u�W�F�N�g�Ǘ�
	Player*player;	//�v���C���[�̃I�u�W�F�N�g�Ǘ�
	Enemy*enemy;	//�G�l�~�[�̃I�u�W�F�N�g�Ǘ�
	HitCheck*hit;
};
