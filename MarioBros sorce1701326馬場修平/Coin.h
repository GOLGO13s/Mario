#pragma once
#include "VECTOR2.h"
#include "VECTOR3.h"

class Coin
{
private:
	VECTOR3 pos;
	VECTOR2 size;
	int animCnt;
	bool getFlag;
public:
	Coin();
	~Coin();
	void SystemInit();	//�摜�ǂݍ���
	void Init();		//�p�����[�^������
	void Draw();		//�`�揈��
	RECT c;					
	//���W��Ԃ�
	VECTOR3&GetPos() {
		return pos;
	}

	//pos���Z�b�g����
	VECTOR3& SetPos(VECTOR3 pos) {
		this->pos = pos;
		return pos;
	}

	//�摜�T�C�Y��Ԃ�
	VECTOR2&GetSize() {
		return size;
	}

	//�Q�b�g�t���O��Ԃ�
	bool GetCoinFlag() {
		return getFlag;
	}
	//�Q�b�g�t���O���Z�b�g����
	void SetCoinFlag(bool flag) {
		if (flag == true) {
			getFlag = true;//���S
		}
		else {
			getFlag = false;//�����Ă���
		}
	}
};

