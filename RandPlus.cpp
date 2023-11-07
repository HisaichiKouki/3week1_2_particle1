#include "RandPlus.h"

int GetRand()
{
	return rand();
}

Vec2f GetRandPos(Vec2f radius)
{
	if (radius.x != 0 && radius.y != 0)
	{
		return Vec2f
		{
			float(rand() % int(radius.x * 4 - (radius.x * 2 - 1))) ,
			float(rand() % int(radius.y * 4 - (radius.y * 2 - 1)))
		};
	}return Vec2f{ 0,0 };
}

int GetRandMinMax(int min, int max)
{
	if (abs(min) + abs(max) != 0)
	{
		return (rand() % (max - min + 1) + min);
	}//(abs(min) + abs(max) - min + 1)
	return 0;
}




