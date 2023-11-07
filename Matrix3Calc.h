#pragma once
//#include "Vector2.h"
#include "MyVector2.h"
struct Matrix3x3
{
	float m[3][3];
};

//Matrix3x3 MakeTranslateMatrix(Vector2 translate);
//
//Vector2 Transform(Vector2 vector, Matrix3x3 matrix);
//
//Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
//
//Matrix3x3 MakeRotateMatrix(float theta);
//
//Matrix3x3 MakeScaleMatrix(Vector2 scale);
//
//Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 translate);


Matrix3x3 MakeTranslateMatrix(Vec2f translate);

Vec2f Transform(Vec2f vector, Matrix3x3 matrix);

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

Matrix3x3 MakeRotateMatrix(float theta);

Matrix3x3 MakeScaleMatrix(Vec2f scale);

Matrix3x3 MakeAffineMatrix(Vec2f scale, float theta, Vec2f translate);

