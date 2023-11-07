#pragma once
//#include "Vector2.h"
#include "Matrix3Calc.h"
#include "MyVector2.h"
//void DrawQuadPlus(Vector2 pos, Vector2 radius,Vector2 src,Vector2 wh,int textur,unsigned color);
//
//void DrawQuadAlpha(Vector2 pos, Vector2 radius, Vector2 scale, float theta, Vector2 src, Vector2 wh, int textur, unsigned color);

void DrawQuadPlus(Vec2f pos, Vec2f radius, Vec2f src, Vec2f wh, int textur, unsigned color);

void DrawQuadAlpha(Vec2f pos, Vec2f radius, Vec2f scale, float theta, Vec2f src, Vec2f wh, int textur, unsigned color);
