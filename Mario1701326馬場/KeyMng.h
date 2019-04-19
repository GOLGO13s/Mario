#pragma once

enum KEY_MODE {
	// ----- P1
	P1_RIGHT,
	P1_LEFT,

	P1_Z,
	P1_C,
	P1_D,
	P1_X,

	P1_LSHIFT,

	P1_SPACE,
	P1_ENTER,
	KEY_MAX
};

// ----- �ݸ���݂�KeyCheck�׽���`����
class KeyMng
{
private:
	// ----- �ݽ�׸��Q
	KeyMng();	// ��̫�ĺݽ�׸���private�ɂ��ĊO�����琶���ł��Ȃ��l�ɂ���
	KeyMng(const KeyMng&){}						// ----- ��߰�ݽ�׸���private��
	KeyMng& operator=(const KeyMng& g){}		// ----- ������Z�q�̵��ްײ�ނ�private��
	~KeyMng(){}	// �޽�׸�
	
public:
	// ----- KeyMng��޼ު�Ă̎��̂�Ԃ�(�ݸ����)
	static KeyMng& GetInstance() {
		static KeyMng keyInstance;	// KeyMng�̎��̂𐶐��BkeyInstance�ɕێ�
		return keyInstance;
	}

	void Init(void);
	bool Update();	// ����ԍX�V(��ٰ�ߍX�V)

	bool newKey[KEY_MAX];
	bool trgKey[KEY_MAX];
	bool upKey[KEY_MAX];
	bool oldKey[KEY_MAX];

	// ----- ����̨��
	// configKey[]�̂��ꂼ��̔ԍ������ꂼ��KEY_MODE�̔ԍ��ɑΉ����Ă���
	// ��)configKey[0] �� P1_UP

	// ���������s���ꍇ�́A����̷����͂��������ꍇnewKey[configkey[�`]]���������ꂽ���ɂ���
	// ��)if(CheckHitKey(KEY_INPUT_RIGHT)) newKey[configKey[2]] = 1;
	// ���E���������ꂽ��2:P1_DOWN�������ꂽ���ɂ���

	int configKey[KEY_MAX];	// ����̨�ޗp�̷��z��
	void SetKeyConfig(int, int);	// ����̨�޾��
};
