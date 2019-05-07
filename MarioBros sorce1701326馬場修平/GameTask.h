#pragma once
#include <list>

class Field;
class Player;
class Enemy;
class Coin;
class HitCheck;

//��ʑJ�ڗp
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
	int GameInit(void);			//��������ǂݍ��݂��s��
	int GameTitle(void);		//�Q�[���^�C�g���\�����s��
	int GameDescription(void);	//�Q�[���������s��
	int GameMain(void);			//�Q�[�����C���̏������s��
	int GameOver(void);			//�Q�[���I�[�o�̏������s��
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
	int graph;	//�O���t�B�b�N�n���h��
	int ecount;	//�G�l�~�[�̃J�E���g
	int score;	//�X�R�A
	int ranking[3];
	Field*field;	//�t�B�[���h�N���X�̃I�u�W�F�N�g�Ǘ�
	Player*player;	//�v���C���[�N���X�̃I�u�W�F�N�g�Ǘ�
	std::list<Enemy*> EnemyList;	//�G�l�~�N���X�[�̃��X�g�Ǘ�;
	Coin*coin;		//�R�C���N���X�̃I�u�W�F�N�g�Ǘ�
	HitCheck*hit;	//�q�b�g�`�F�b�N�N���X�̃I�u�W�F�N�g�Ǘ�
};
