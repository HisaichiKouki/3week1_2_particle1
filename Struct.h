#pragma once
#include "Color.h"
#include "MyVector2.h"



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
	bool particleSpawnFlag ;//フラグでパーティクル発生
	int particleTimerMax ;//発生持続時間を設定
	int particleTimerCount;//発生持続時間をカウント
	float particleBound;//バウンドの係数
}Emitter;