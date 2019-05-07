#include <DxLib.h>
#include "KeyMng.h"

KeyMng::KeyMng()
{
	Init();
}

void KeyMng::Init()
{
	// ----- ﾌﾗｸﾞ全ｸﾘｱ
	// ※configもｸﾘｱされる
	for(int i = 0; i < KEY_MAX; i++){
		newKey[i] = false;
		trgKey[i] = false;
		upKey[i] = false;
		oldKey[i] = false;
		configKey[i] = i;	
	}
}

bool KeyMng::Update()
{
	for(int i = 0; i < KEY_MAX; i++){
		newKey[i] = false;	// 全部押していない事にする
		trgKey[i] = false;	// 全部押していない事にする
		upKey[i] = false;	// 全部押していない事にする
	}

	// ----- newKey
	
	if(CheckHitKey(KEY_INPUT_RIGHT)) newKey[P1_RIGHT] = true;
	if(CheckHitKey(KEY_INPUT_LEFT)) newKey[P1_LEFT] = true;

	if(CheckHitKey(KEY_INPUT_Z)) newKey[P1_Z] = true;
	if(CheckHitKey(KEY_INPUT_C)) newKey[P1_C] = true;
	if(CheckHitKey(KEY_INPUT_D)) newKey[P1_D] = true;
	if(CheckHitKey(KEY_INPUT_X)) newKey[P1_X] = true;

	if(CheckHitKey(KEY_INPUT_LSHIFT)) newKey[P1_LSHIFT] = true;
	
	if(CheckHitKey(KEY_INPUT_SPACE))newKey[P1_SPACE] = true;
	if(CheckHitKey(KEY_INPUT_RETURN))newKey[P1_ENTER] = true;

	// ----- trgKey & upKey & oldKey
	for(int i = 0; i < KEY_MAX; i++){
		trgKey[i] = newKey[i] & ~oldKey[i];	// trgKey
		upKey[i] = ~newKey[i] & oldKey[i];	// upKey
		oldKey[i] = newKey[i];	// oldKey
	}
	return true;
}

void KeyMng::SetKeyConfig(int n, int after)
{
	configKey[n] = after;
}