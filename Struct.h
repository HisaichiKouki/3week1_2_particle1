#pragma once
#include "Color.h"

struct Vector2
{
	float x;
	float y;
};


typedef struct Particle
{
	Vector2 pos;
	Vector2 velocity;
	Vector2 acceleration;
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
	Vector2 pos;
	Vector2 radius;
	float minLife;
	float maxLife;
	Vector2 direction;
	Color color;
}Emitter;