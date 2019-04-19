#pragma once
#include "VECTOR2.h"

constexpr int MAP_CHIP_SIZE(32);	//�}�b�v�`�b�v�̑傫��
constexpr int MAP_WIDTH(16);		//�}�b�v�̕�(��)
constexpr int MAP_HEIGHT(16);		//�}�b�v�̍���(�c)

class Field
{
private:
	int chip[256];
public:
	RECT m[MAP_HEIGHT][MAP_WIDTH];	// �\�������`�̃Z�b�g
	Field();
	~Field();
	void Init();		//�p�����[�^������
	void Draw();		//�`�揈��
	int GetMapData(float X,float Y);	//�}�b�v�f�[�^�̒l��Ԃ�
};

