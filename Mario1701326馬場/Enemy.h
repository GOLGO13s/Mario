#pragma once
#include "VECTOR2.h"
#include "VECTOR3.h"

class Enemy
{
private:
	VECTOR3 pos;
	VECTOR2 size;
	float speed;
	bool lrFlag;
	bool deadFlag;
	int animCnt;
public:
	Enemy();
	~Enemy();
	void SystemInit();	//�摜�ǂݍ���
	void Init();		//�p�����[�^������
	void Update();		//�ړ�����
	void Draw();		//�`�揈��
	RECT e;

	//���W��Ԃ�
	VECTOR3&GetPos() {
		return pos;
	}

	//pos���Z�b�g����
	VECTOR3& SetPos(VECTOR3 pos) {
		this->pos = pos;
		return pos;
	}
	
	//�Î~���ƈړ����̃T�C�Y��Ԃ�
	VECTOR2&GetSize() {
		return size;

	}

	//���S�t���O��Ԃ�
	bool GetDeadFlag() {
		return deadFlag;
	}
	//���S�t���O���Z�b�g����
	void SetDeadFlag(bool flag) {
		if (flag == true) {
			deadFlag = true;//���S
		}
		else {
			deadFlag = false;//�����Ă���
		}
	}

};

