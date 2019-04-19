#pragma once
#include "VECTOR2.h"
#include "VECTOR3.h"
class HitCheck
{
public:
	HitCheck();
	~HitCheck();
	bool Hit(RECT rect1, RECT rect2);

};

