#pragma once
#include "VECTOR2.h"
#include "VECTOR3.h"

class Enemy
{
private:
	VECTOR3 pos;
	VECTOR2 size;
	float G;
	float speed;
	int animCnt;
	
	bool lrFlag;
	bool dyingFlag;	//�m����ԃt���O(�G�͏����Ȃ�)
	bool deathFlag;	//���S��ԃt���O(�G������)
	bool getcoinFlag;
	bool ehitBFlag;
	bool movFlag;
public:
	Enemy();
	~Enemy();
	void SystemInit();	//�摜�ǂݍ���
	void Init();		//�p�����[�^������
	void Update();		//�ړ�����
	void Draw();		//�`�揈��
	RECT e;
	int revivalCnt;
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
	bool GetDyingFlag() {
		return dyingFlag;
	}
	//���S�t���O���Z�b�g����
	void SetDyingFlag(bool flag) {
		if (flag == true) {
			dyingFlag = true;//���S
		}
		else {
			dyingFlag = false;//�����Ă���
		}
	}

	//���S�t���O��Ԃ�
	bool GetDeathFlag() {
		return deathFlag;
	}

	//���S�t���O���Z�b�g����
	void SetDeathFlag(bool flag) {
		if (flag == true) {
			deathFlag = true;//���S
		}
		else {
			deathFlag = false;//�����Ă���
		}
	}

	//���S�t���O��Ԃ�
	bool GetEHitBFlag() {
		return ehitBFlag;
	}
	//���S�t���O���Z�b�g����
	void SetEHitBFlag(bool flag) {
		if (flag == true) {
			ehitBFlag = true;//���S
		}
		else {
			ehitBFlag = false;//�����Ă���
		}
	}

};

