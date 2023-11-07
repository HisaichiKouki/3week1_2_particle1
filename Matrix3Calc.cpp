#include "Matrix3Calc.h"
#include <assert.h>
#include <corecrt_math.h>

//Matrix3x3 MakeTranslateMatrix(Vector2 translate)
//{
//
//	Matrix3x3 A{};
//	A.m[0][0] = 1.0f;
//	A.m[1][1] = 1.0f;
//	A.m[2][2] = 1.0f;
//	A.m[2][0] = translate.x;
//	A.m[2][1] = translate.y;
//	return Matrix3x3(A);
//}
//
//Vector2 Transform(Vector2 vector, Matrix3x3 matrix)
//{
//	Vector2 result;
//	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
//	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
//	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
//
//	assert(w != 0.0f);
//	result.x /= w;
//	result.y /= w;
//	return result;
//}
//
//Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
//{
//
//	Matrix3x3 result{};
//	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
//	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
//	result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
//	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
//	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
//	result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
//	result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
//	result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
//	result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];
//
//
//	return Matrix3x3(result);
//}
//
//Matrix3x3 MakeRotateMatrix(float theta)
//{
//	Matrix3x3 rotate{};
//	rotate.m[0][0] = cosf(theta);
//	rotate.m[0][1] = sinf(theta);
//	rotate.m[1][0] = -sinf(theta);
//	rotate.m[1][1] = cosf(theta);
//	rotate.m[2][2] = 1.0f;
//	return Matrix3x3(rotate);
//}
//
//Matrix3x3 MakeScaleMatrix(Vector2 scale)
//{
//	Matrix3x3 result{};
//	result.m[0][0] = scale.x;
//	result.m[1][1] = scale.y;
//	result.m[2][2] = 1;
//	return Matrix3x3(result);
//}
//
//Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 translate)
//{
//
//	Matrix3x3 result{};
//	result.m[0][0] = scale.x * cosf(theta);
//	result.m[0][1] = scale.x * sinf(theta);
//	result.m[1][0] = scale.y * -sinf(theta);
//	result.m[1][1] = scale.y * cosf(theta);
//	result.m[2][0] = translate.x;
//	result.m[2][1] = translate.y;
//	result.m[2][2] = 1.0f;
//
//	return Matrix3x3(result);
//}


Matrix3x3 MakeTranslateMatrix(Vec2f translate)
{

	Matrix3x3 A{};
	A.m[0][0] = 1.0f;
	A.m[1][1] = 1.0f;
	A.m[2][2] = 1.0f;
	A.m[2][0] = translate.x;
	A.m[2][1] = translate.y;
	return Matrix3x3(A);
}

Vec2f Transform(Vec2f vector, Matrix3x3 matrix)
{
	Vec2f result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{

	Matrix3x3 result{};
	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
	result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];


	return Matrix3x3(result);
}

Matrix3x3 MakeRotateMatrix(float theta)
{
	Matrix3x3 rotate{};
	rotate.m[0][0] = cosf(theta);
	rotate.m[0][1] = sinf(theta);
	rotate.m[1][0] = -sinf(theta);
	rotate.m[1][1] = cosf(theta);
	rotate.m[2][2] = 1.0f;
	return Matrix3x3(rotate);
}

Matrix3x3 MakeScaleMatrix(Vec2f scale)
{
	Matrix3x3 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = 1;
	return Matrix3x3(result);
}

Matrix3x3 MakeAffineMatrix(Vec2f scale, float theta, Vec2f translate)
{

	Matrix3x3 result{};
	result.m[0][0] = scale.x * cosf(theta);
	result.m[0][1] = scale.x * sinf(theta);
	result.m[1][0] = scale.y * -sinf(theta);
	result.m[1][1] = scale.y * cosf(theta);
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;

	return Matrix3x3(result);
}
