#include "RandPlus.h"

int GetRand()
{
	return rand();
}

Vector2 GetRandPos(Vector2 radius)
{
	if (radius.x != 0 && radius.y != 0) return Vector2({ float(rand() % int(radius.x * 4 - (radius.x * 2 - 1))) , float(rand() % int(radius.y * 4 - (radius.y * 2 - 1))) });
	return Vector2{ 0,0 };
}

int GetRandMinMax(int min, int max)
{
	if (abs(min) + abs(max) != 0)return (rand() % (max - min+1) + min);//(abs(min) + abs(max) - min + 1)
	return 0;
}




