#pragma once
#include "Color.h"
#include "MyVector2.h"
//struct Vector2
//{
//	float x;
//	float y;
//};


typedef struct Particle
{
	Vec2f pos;
	Vec2f velocity;
	Vec2f acceleration;
	float radius;
	float lifeTime;
	float currentTime;
	Color color;
	float raito;
	float max;
	float boundPoint;
}Particle;
typedef struct Emitter
{
	Vec2f pos;
	Vec2f radius;
	float minLife;
	float maxLife;
	Vec2f direction;
	Color color;
}Emitter;