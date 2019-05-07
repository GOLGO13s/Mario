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

// ----- ｼﾝｸﾞﾙﾄﾝのKeyCheckｸﾗｽを定義する
class KeyMng
{
private:
	// ----- ｺﾝｽﾄﾗｸﾀ群
	KeyMng();	// ﾃﾞﾌｫﾙﾄｺﾝｽﾄﾗｸﾀをprivateにして外部から生成できない様にする
	KeyMng(const KeyMng&){}						// ----- ｺﾋﾟｰｺﾝｽﾄﾗｸﾀをprivate化
	KeyMng& operator=(const KeyMng& g){}		// ----- 代入演算子のｵｰﾊﾞｰﾗｲﾄﾞをprivate化
	~KeyMng(){}	// ﾃﾞｽﾄﾗｸﾀ
	
public:
	// ----- KeyMngｵﾌﾞｼﾞｪｸﾄの実体を返す(ｼﾝｸﾞﾙﾄﾝ)
	static KeyMng& GetInstance() {
		static KeyMng keyInstance;	// KeyMngの実体を生成。keyInstanceに保持
		return keyInstance;
	}

	void Init(void);
	bool Update();	// ｷｰ状態更新(毎ﾙｰﾌﾟ更新)

	bool newKey[KEY_MAX];
	bool trgKey[KEY_MAX];
	bool upKey[KEY_MAX];
	bool oldKey[KEY_MAX];

	// ----- ｷｰｺﾝﾌｨｸﾞ
	// configKey[]のそれぞれの番号がそれぞれKEY_MODEの番号に対応している
	// 例)configKey[0] ← P1_UP

	// ｷｰﾁｪｯｸを行う場合は、所定のｷｰ入力があった場合newKey[configkey[～]]が押下された事にする
	// 例)if(CheckHitKey(KEY_INPUT_RIGHT)) newKey[configKey[2]] = 1;
	// ※右ｷｰが押されたら2:P1_DOWNが押された事にする

	int configKey[KEY_MAX];	// ｷｰｺﾝﾌｨｸﾞ用のｷｰ配列
	void SetKeyConfig(int, int);	// ｷｰｺﾝﾌｨｸﾞｾｯﾄ
};
