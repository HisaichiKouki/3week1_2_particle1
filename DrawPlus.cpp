#include <Novice.h>
#include "DrawPlus.h"


//void DrawQuadPlus(Vector2 pos, Vector2 radius, Vector2 src, Vector2 wh, int textur, unsigned color)
//{
//	return Novice::DrawQuad(int(pos.x - radius.x), int(pos.y - radius.y),
//		int(pos.x + radius.x), int(pos.y - radius.y),
//		int(pos.x - radius.x), int(pos.y + radius.y),
//		int(pos.x + radius.x), int(pos.y + radius.y)
//		, int(src.x), int(src.y), int(wh.x), int(wh.y), textur, color);
//}
//
//void DrawQuadAlpha(Vector2 pos, Vector2 radius, Vector2 scale, float theta, Vector2 src, Vector2 wh, int textur, unsigned color)
//{
//
//	Matrix3x3 resultMatrix = MakeAffineMatrix(scale, theta, pos);
//
//	Vector2 leftTop = Transform({ -radius.x,-radius.y }, resultMatrix);
//	Vector2 rightTop = Transform({ +radius.x,-radius.y }, resultMatrix);
//	Vector2 leftBottom = Transform({ -radius.x,+radius.y }, resultMatrix);
//	Vector2 rightBottom = Transform({ +radius.x,+radius.y }, resultMatrix);
//
//	return Novice::DrawQuad(int(leftTop.x), int(leftTop.y),
//		int(rightTop.x), int(rightTop.y),
//		int(leftBottom.x), int(leftBottom.y),
//		int(rightBottom.x), int(rightBottom.y)
//		, int(src.x), int(src.y), int(wh.x), int(wh.y), textur, color);
//
//}


void DrawQuadPlus(Vec2f pos, Vec2f radius, Vec2f src, Vec2f wh, int textur, unsigned color)
{
	return Novice::DrawQuad(int(pos.x - radius.x), int(pos.y - radius.y),
		int(pos.x + radius.x), int(pos.y - radius.y),
		int(pos.x - radius.x), int(pos.y + radius.y),
		int(pos.x + radius.x), int(pos.y + radius.y)
		, int(src.x), int(src.y), int(wh.x), int(wh.y), textur, color);
}

void DrawQuadAlpha(Vec2f pos, Vec2f radius, Vec2f scale, float theta, Vec2f src, Vec2f wh, int textur, unsigned color)
{

	Matrix3x3 resultMatrix = MakeAffineMatrix(scale, theta, pos);

	Vec2f leftTop = Transform({ -radius.x,-radius.y }, resultMatrix);
	Vec2f rightTop = Transform({ +radius.x,-radius.y }, resultMatrix);
	Vec2f leftBottom = Transform({ -radius.x,+radius.y }, resultMatrix);
	Vec2f rightBottom = Transform({ +radius.x,+radius.y }, resultMatrix);

	return Novice::DrawQuad(int(leftTop.x), int(leftTop.y),
		int(rightTop.x), int(rightTop.y),
		int(leftBottom.x), int(leftBottom.y),
		int(rightBottom.x), int(rightBottom.y)
		, int(src.x), int(src.y), int(wh.x), int(wh.y), textur, color);

}
