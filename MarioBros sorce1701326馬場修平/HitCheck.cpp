#include "DxLib.h"
#include "HitCheck.h"


HitCheck::HitCheck()
{
}


HitCheck::~HitCheck()
{
}

bool HitCheck::Hit(RECT rect1, RECT rect2)
{
	if (rect1.left <= rect2.right &&rect1.top <= rect2.bottom
		&&rect1.right >= rect2.left &&rect1.bottom >= rect2.top) {
		return true;
	}
	else {
		return false;
	}
}








