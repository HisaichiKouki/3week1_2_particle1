#include "Color.h"
//typedef struct Color
//{
//	unsigned int color[4];//0 RED 1 GREEN 2 BLUE 3 ALPHA
//}Color;

unsigned int DegreeColorTranceforme(Color befor)
{
	return befor.color[3] + (befor.color[0] << 24) + (befor.color[1] << 16) + (befor.color[2] << 8);
}



unsigned int ColorGradation(Color befor, Color after, float raito, float max)
{
	if (raito < max)
	{

		return unsigned int((float((max - raito) / max)) * befor.color[3] + after.color[3] * (raito / max)) + unsigned int(unsigned int((float((max - raito) / max)) * befor.color[0] + after.color[0] * (raito / max)) << 24) + unsigned int(unsigned int((float((max - raito) / max)) * befor.color[1] + after.color[1] * (raito / max)) << 16) + unsigned int(unsigned int((float((max - raito) / max)) * befor.color[2] + after.color[2] * (raito / max)) << 8);

	}
	else
	{
		return after.color[3] + (after.color[0] << 24) + (after.color[1] << 16) + (after.color[2] << 8);

	}
}