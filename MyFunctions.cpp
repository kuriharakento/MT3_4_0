#include "MyFunctions.h"

#include <algorithm>
#include <Novice.h>
#include <assert.h>

/// \brief コタンジェント
/// \param a 
/// \return 
float cot(float a) { return cos(a) / sin(a); }

//=======================================================================
//							Matrix4x4
//=======================================================================

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result.m[row][col] = m1.m[row][col] + m2.m[row][col];
		}
	}

	return  result;
}

Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result.m[row][col] = m1.m[row][col] - m2.m[row][col];
		}
	}

	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			result.m[row][column] = m1.m[row][0] * m2.m[0][column] + m1.m[row][1] * m2.m[1][column] + m1.m[row][2] * m2.m[2][column] + m1.m[row][3] * m2.m[3][column];
		}
	}
	return result;
}

Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 result;
	float a;
	Matrix4x4 b;

	a = 1 / (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	b.m[0][0] = m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2];
	b.m[0][1] = -m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2];
	b.m[0][2] = m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2];
	b.m[0][3] = -m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2];

	b.m[1][0] = -m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2];
	b.m[1][1] = m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2];
	b.m[1][2] = -m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2];
	b.m[1][3] = +m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2];

	b.m[2][0] = m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1];
	b.m[2][1] = -m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1];
	b.m[2][2] = m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1];
	b.m[2][3] = -m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1];

	b.m[3][0] = -m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
		+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1];
	b.m[3][1] = +m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1];
	b.m[3][2] = -m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
		+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1];
	b.m[3][3] = m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1];

	result.m[0][0] = a * b.m[0][0]; result.m[0][1] = a * b.m[0][1]; result.m[0][2] = a * b.m[0][2]; result.m[0][3] = a * b.m[0][3];
	result.m[1][0] = a * b.m[1][0]; result.m[1][1] = a * b.m[1][1]; result.m[1][2] = a * b.m[1][2]; result.m[1][3] = a * b.m[1][3];
	result.m[2][0] = a * b.m[2][0]; result.m[2][1] = a * b.m[2][1]; result.m[2][2] = a * b.m[2][2]; result.m[2][3] = a * b.m[2][3];
	result.m[3][0] = a * b.m[3][0]; result.m[3][1] = a * b.m[3][1]; result.m[3][2] = a * b.m[3][2]; result.m[3][3] = a * b.m[3][3];


	return result;
}


Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 m = {
		1,0,0,0,
		0,std::cos(radian),std::sin(radian),0,
		0,-std::sin(radian),std::cos(radian),0,
		0,0,0,1
	};
	return m;
}

Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 m = {
		std::cos(radian),0,-std::sin(radian),0,
		0,1,0,0,
		std::sin(radian),0,std::cos(radian),0,
		0,0,0,1
	};
	return m;
}

Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 m = {
		std::cos(radian),std::sin(radian),0,0,
		-std::sin(radian),std::cos(radian),0,0,
		0,0,1,0,
		0,0,0,1
	};
	return m;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{

	///==================================
	///平行移動の4x4行列の生成
	///==================================

	Matrix4x4 scaleMatrix = {
		scale.x,0,0,0,
		0,scale.y,0,0,
		0,0,scale.z,0,
		0,0,0,1
	};


	///==================================
	///回転で使う4x4行列の宣言
	///==================================

	Matrix4x4 rotateMatrix;
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);		//X軸の回転
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);		//Y軸の回転
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);		//Z軸の回転

	///=================================
	///回転の合成
	///=================================

	rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));


	///==================================
	///平行移動の4x4行列の生成
	///==================================

	Matrix4x4 translateMatrix = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		translate.x,translate.y,translate.z,1
	};


	///==================================
	///3次元のアフィン変換
	///==================================

	Matrix4x4 weight = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);

	//アフィン変換した値を返す
	return weight;

}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 m{
		2 / (right - left),0,0,0,
		0,2 / (top - bottom),0,0,
		0,0,1 / (farClip - nearClip),0,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1
	};

	return m;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 m{
	1 / aspectRatio * cot(fovY / 2), 0, 0, 0,
		0, cot(fovY / 2), 0, 0,
		0, 0, farClip / (farClip - nearClip), 1,
		0,0,(-nearClip * farClip) / (farClip - nearClip),0
	};
	return m;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 m{
		width / 2,0,0,0,
		0,-height / 2,0,0,
		0,0,maxDepth - minDepth,0,
		left + (width / 2),top + (height / 2),minDepth,1
	};
	return m;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

float Length(const Vector3& v1, const Vector3& v2)
{
	Vector3 distance;
	float d;

	distance = v2 - v1;
	d = sqrtf(powf(distance.x, 2) + powf(distance.y, 2) + powf(distance.z, 2));

	return d;
}

float Length(const Vector3& v) {
	float result;
	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
}


void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfwidth = 2.0f;                                     //Gridの半分
	const uint32_t kSubdivision = 10;                                      //分割数
	const float kGridEvery = (kGridHalfwidth * 2.0f) / float(kSubdivision);//1つ分の長さ

	//奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex)
	{
		//上の情報を使ってワールド座標系上の始点と終点を求める
		Vector3 zStart, zEnd;
		zStart = Vector3(xIndex * kGridEvery - kGridHalfwidth, 0, 2);
		zEnd = Vector3(xIndex * kGridEvery - kGridHalfwidth, 0, -6);

		//スクリーン座標系まで変換をかける
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, zStart);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, zEnd);

		Matrix4x4 startwvpMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endwvpMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);

		Vector3 startLocal = Transform(zStart, startwvpMatrix);
		Vector3 endLocal = Transform(zEnd, endwvpMatrix);

		Vector3 startScreen = Transform(startLocal, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, viewportMatrix);

		//変換した座標を使って表示、色は薄い灰色(0xAAAAAAFF)。原点は黒
		if (xIndex == kSubdivision / 2)
		{
			Novice::DrawLine(
				(int)startScreen.x, (int)startScreen.y,
				(int)endScreen.x, (int)endScreen.y,
				BLACK
			);
		}
		else
		{
			Novice::DrawLine(
				(int)startScreen.x, (int)startScreen.y,
				(int)endScreen.x, (int)endScreen.y,
				0xAAAAAAFF
			);
		}

	}

	//左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
	{
		//奥から手前が左右に変わるだけ
		//上の情報を使ってワールド座標系上の始点と終点を求める
		Vector3 xStart, xEnd;

		xStart = Vector3(2, 0, zIndex * kGridEvery - kGridHalfwidth);
		xEnd = Vector3(-2, 0, zIndex * kGridEvery - kGridHalfwidth);

		//スクリーン座標系まで変換をかける
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, xStart);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, xEnd);

		Matrix4x4 startwvpMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endwvpMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);

		Vector3 startLocal = Transform(xStart, startwvpMatrix);
		Vector3 endLocal = Transform(xEnd, endwvpMatrix);

		Vector3 startScreen = Transform(startLocal, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, viewportMatrix);

		//変換した座標を使って表示、色は薄い灰色(0xAAAAAAFF)。原点は黒
		if (zIndex == kSubdivision / 2)
		{
			Novice::DrawLine(
				(int)startScreen.x, (int)startScreen.y,
				(int)endScreen.x, (int)endScreen.y,
				BLACK
			);
		}
		else
		{
			Novice::DrawLine(
				(int)startScreen.x, (int)startScreen.y,
				(int)endScreen.x, (int)endScreen.y,
				0xAAAAAAFF
			);
		}
	}

}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const float pi = 3.1415926535f;
	const uint32_t kSubdivision = 16;//分割数
	const float kLatEvery = pi / kSubdivision;   //経度分割1つ分の角度
	const float kLonEvery = (2 * pi) / kSubdivision;   //緯度分割1つ分の角度

	//緯度の方向に分割 -π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex)
	{
		sphere;
		float lat = -pi / 2.0f + kLatEvery * latIndex;//現在の緯度

		//経度の方向に分割 0 ～ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
		{
			float lon = lonIndex * kLonEvery;//現在の経度

			//world座標系でのa,b,c,を求める
			Vector3 a, b, c;
			a = {
				(sphere.radius) * std::cos(lat) * std::cos(lon),
				(sphere.radius) * std::sin(lat),
				(sphere.radius) * std::cos(lat) * std::sin(lon)
			};
			b = {
				(sphere.radius) * std::cos(lat + (pi / kSubdivision)) * std::cos(lon),
				(sphere.radius) * std::sin(lat + (pi / kSubdivision)),
				(sphere.radius) * std::cos(lat + (pi / kSubdivision)) * std::sin(lon)
			};
			c = {
				(sphere.radius) * std::cos(lat) * std::cos(lon + ((pi * 2) / kSubdivision)),
				(sphere.radius) * std::sin(lat),
				(sphere.radius) * std::cos(lat) * std::sin(lon + ((pi * 2) / kSubdivision))
			};

			//a,b,cをScreen座標系まで変換...
			Matrix4x4 aWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 bWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 cWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);



			Matrix4x4 awvpMatrix = Multiply(aWorldMatrix, viewProjectionMatrix);
			Matrix4x4 bwvpMatrix = Multiply(bWorldMatrix, viewProjectionMatrix);
			Matrix4x4 cwvpMatrix = Multiply(cWorldMatrix, viewProjectionMatrix);

			Vector3 aLocal = Transform(a, awvpMatrix);
			Vector3 bLocal = Transform(b, bwvpMatrix);
			Vector3 cLocal = Transform(c, cwvpMatrix);

			Vector3 aScreen = Transform(aLocal, viewportMatrix);
			Vector3 bScreen = Transform(bLocal, viewportMatrix);
			Vector3 cScreen = Transform(cLocal, viewportMatrix);

			//ab,bcで線を引く
			Novice::DrawLine(
				(int)aScreen.x, (int)aScreen.y,
				(int)bScreen.x, (int)bScreen.y,
				color
			);
			Novice::DrawLine(
				(int)aScreen.x, (int)aScreen.y,
				(int)cScreen.x, (int)cScreen.y,
				color
			);
		}

	}

}


//=======================================================================
//							Vector3
//=======================================================================

Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

float Dot(Vector3 v1, Vector3 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector3 Normalize(const Vector3& v)
{
	Vector3 result;
	result.x = v.x / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	result.y = v.y / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	result.z = v.z / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{
		(v1.y * v2.z) - (v1.z * v2.y),(v1.z * v2.x) - (v1.x * v2.z),(v1.x * v2.y) - (v1.y * v2.x)
	};
	return result;
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	float ab = Dot(v1, v2);
	float normB = std::sqrt(Dot(v2, v2));
	float t = ab / std::pow(normB, 2.0f);
	return Vector3(t * v2.x, t * v2.y, t * v2.z);

}

//修正したためミスがあったらMT3_2_1参照
Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 proja = Project(point - segment.origin, (segment.origin + segment.diff) - segment.origin);
	Vector3 cp = segment.origin + proja;

	return cp;
}

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	float dis = s1.radius + s2.radius;

	Vector3 dist = { s1.center.x - s2.center.x ,s1.center.y - s2.center.y,s1.center.z - s2.center.z };

	float distance = sqrtf(powf(dist.x, 2) + powf(dist.y, 2) + powf(dist.z, 2));

	if (distance <= dis)
	{
		return true;
	}
	else
	{
		return false;
	}

}

Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f)
	{
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	float k = sqrtf(powf(Dot(plane.normal, sphere.center) - plane.distance, 2));

	if (k <= sphere.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 center = Multiply(plane.distance, plane.normal); // 1
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal)); // 2
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z }; // 3
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]); // 4
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z }; // 5

	// 6
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index)
	{
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = center + extend;
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	//points をそれぞれ結んでDraw で矩形を描画する。DrawTringleを使って塗りつぶしても良いが、DepthがないのでMT3では分かりずらい
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
}

bool isColision(const Segment& segment, const Plane& plane)
{
	//法線と線の内積
	float dot = Dot(plane.normal, segment.diff);

	//平行なので衝突しない
	if (dot == 0.0f)
	{
		return false;
	}

	//tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	//衝突判定
	if (t <= 1 && t >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	//スクリーン座標に変換
	Vector3 transform[3];
	Vector3 screen[3];

	for (int i = 0; i < 3; ++i) {
		transform[i] = Transform(triangle.vertices[i], viewProjectionMatrix);
		screen[i] = Transform(transform[i], viewportMatrix);
	}

	//三角形の描画
	Novice::DrawTriangle((int)screen[0].x, (int)screen[0].y, (int)screen[1].x, (int)screen[1].y, (int)screen[2].x, (int)screen[2].y, color, kFillModeWireFrame);
}

bool isCollision(const Segment& segment, const Triangle& triangle)//平面求めてから判定を取るー＞三角形との積をなんやかんや
{

	Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
	Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
	Vector3 v20 = triangle.vertices[0] - triangle.vertices[2];

	Vector3 n = Normalize(Cross(v01, v12));

	float d = Dot(triangle.vertices[0], n);

	//法線と線の内積
	float dot = Dot(n, segment.diff);

	float t = (d - Dot(segment.origin, n)) / dot;

	if (!(t <= 1 && t >= 0))
	{
		return false;
	}

	Vector3 p = segment.origin + Multiply(t, segment.diff);

	Vector3 v0p = p-triangle.vertices[0];
	Vector3 v1p = p- triangle.vertices[1];
	Vector3 v2p = p- triangle.vertices[2];

	//各辺を結んだベクトル、頂点、衝突点pを結んだベクトルのクロス積を取る
	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	//衝突判定
	if (Dot(cross01, n) >= 0.0f &&
		Dot(cross12, n) >= 0.0f &&
		Dot(cross20, n) >= 0.0f) {
		return true;
	}
	else {
		return false;
	}
}

//AABB・AABB
bool isCollision(const AABB& aabb1, const AABB& aabb2)
{
	//衝突判定
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z))
	{
		return true;
	} else
	{
		return false;
	}
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	//8頂点求める
	Vector3 flontLeftUp{ aabb.min.x,aabb.max.y,aabb.min.z };
	Vector3 flontLeftUnder{ aabb.min.x,aabb.min.y,aabb.min.z };
	Vector3 flontRightUp{ aabb.max.x,aabb.max.y,aabb.min.z };
	Vector3 flontRightUnder{ aabb.max.x,aabb.min.y,aabb.min.z };

	Vector3 backLeftUp{ aabb.min.x,aabb.max.y,aabb.max.z };
	Vector3 backLeftUnder{ aabb.min.x,aabb.min.y,aabb.max.z };
	Vector3 backRightUp{ aabb.max.x,aabb.max.y,aabb.max.z };
	Vector3 backRightUnder{ aabb.max.x,aabb.min.y,aabb.max.z };

	//スクリーン座標に変換
	Vector3 transform[8];
	Vector3 screen[8];

	transform[0] = Transform(flontLeftUp, viewProjectionMatrix);
	transform[1] = Transform(flontLeftUnder, viewProjectionMatrix);
	transform[2] = Transform(flontRightUp, viewProjectionMatrix);
	transform[3] = Transform(flontRightUnder, viewProjectionMatrix);

	transform[4] = Transform(backLeftUp, viewProjectionMatrix);
	transform[5] = Transform(backLeftUnder, viewProjectionMatrix);
	transform[6] = Transform(backRightUp, viewProjectionMatrix);
	transform[7] = Transform(backRightUnder, viewProjectionMatrix);

	screen[0] = Transform(transform[0], viewportMatrix);
	screen[1] = Transform(transform[1], viewportMatrix);
	screen[2] = Transform(transform[2], viewportMatrix);
	screen[3] = Transform(transform[3], viewportMatrix);

	screen[4] = Transform(transform[4], viewportMatrix);
	screen[5] = Transform(transform[5], viewportMatrix);
	screen[6] = Transform(transform[6], viewportMatrix);
	screen[7] = Transform(transform[7], viewportMatrix);

	//8頂点線で結ぶ
	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[1].x, (int)screen[1].y, color);
	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[2].x, (int)screen[2].y, color);
	Novice::DrawLine((int)screen[0].x, (int)screen[0].y, (int)screen[4].x, (int)screen[4].y, color);

	Novice::DrawLine((int)screen[6].x, (int)screen[6].y, (int)screen[2].x, (int)screen[2].y, color);
	Novice::DrawLine((int)screen[6].x, (int)screen[6].y, (int)screen[4].x, (int)screen[4].y, color);
	Novice::DrawLine((int)screen[6].x, (int)screen[6].y, (int)screen[7].x, (int)screen[7].y, color);

	Novice::DrawLine((int)screen[5].x, (int)screen[5].y, (int)screen[1].x, (int)screen[1].y, color);
	Novice::DrawLine((int)screen[5].x, (int)screen[5].y, (int)screen[4].x, (int)screen[4].y, color);
	Novice::DrawLine((int)screen[5].x, (int)screen[5].y, (int)screen[7].x, (int)screen[7].y, color);

	Novice::DrawLine((int)screen[3].x, (int)screen[3].y, (int)screen[1].x, (int)screen[1].y, color);
	Novice::DrawLine((int)screen[3].x, (int)screen[3].y, (int)screen[2].x, (int)screen[2].y, color);
	Novice::DrawLine((int)screen[3].x, (int)screen[3].y, (int)screen[7].x, (int)screen[7].y, color);

}

bool isCollision(const AABB& aabb, const Sphere& sphere)
{
	//最接点を求める
	Vector3 closestPoint{
	 std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
	 std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
	 std::clamp(sphere.center.z,aabb.min.z,aabb.max.z) };

	//最接点と球の中心との距離を求める
	float distance = Length(closestPoint, sphere.center);

	//距離が半径よりも小さければ衝突
	if (distance < sphere.radius)
	{
		return true;
	} else
	{
		return false;
	}

}


bool isCollision(const AABB& aabb, const Segment segment)
{
	Vector3 nX = { 1,0,0 };
	Vector3 nY = { 0,1,0 };
	Vector3 nZ = { 0,0,1 };

	float dotX = Dot(nX, segment.diff);
	float dotY = Dot(nY, segment.diff);
	float dotZ = Dot(nZ, segment.diff);

	//Vector3 dot = Add(segment.origin, segment.diff);

	float txMin = (aabb.min.x - segment.origin.x) / dotX;
	float txMax = (aabb.max.x - segment.origin.x) / dotX;

	float tyMin = (aabb.min.y - segment.origin.y) / dotY;
	float tyMax = (aabb.max.y - segment.origin.y) / dotY;

	float tzMin = (aabb.min.z - segment.origin.z) / dotZ;
	float tzMax = (aabb.max.z - segment.origin.z) / dotZ;


	float tNearX = min(txMin, txMax);
	float tFarX = max(txMin, txMax);

	float tNearY = min(tyMin, tyMax);
	float tFarY = max(tyMin, tyMax);

	float tNearZ = min(tzMin, tzMax);
	float tFarZ = max(tzMin, tzMax);



	//AABBとの衝突点（貫通点）のtが小さい方
	float tmin = max(max(tNearX, tNearY), tNearZ);

	//AABBとの衝突点（貫通点）のtが大きい方
	float tmax = min(min(tFarX, tFarY), tFarZ);



	if (txMax > INFINITY or txMin < -INFINITY or
		tyMax > INFINITY or tyMin < -INFINITY or
		tzMax > INFINITY or tzMin < -INFINITY)
	{
		return false;
	}

	if (std::isnan(txMax) or std::isnan(txMin) or
		std::isnan(tyMax) or std::isnan(tyMin) or
		std::isnan(tzMax) or std::isnan(tzMin))
	{
		return false;
	}

	//衝突判定
	if (tmin <= tmax)
	{
		if ((tmax <= 1 && tmax >= 0) or (tmin <= 1 && tmin >= 0))
		{
			return true;
		} else if ((tFarX >= 1 && tNearX <= 0) &&
			(tFarY >= 1 && tNearY <= 0) &&
			(tFarZ >= 1 && tNearZ <= 0))
		{
			return true;
		} else
		{
			return false;
		}

	} else
	{
		return false;
	}

}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	Vector3 result;
	result = v1  Multiply(t, v2 - v1);
	return result;
}

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t)
{
	Vector3 p0p1 = Lerp(p0, p1, t);
	Vector3 p1p2 = Lerp(p1, p2, t);
	Vector3 p = Lerp(p0p1, p1p2, t);

	return p;
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
                const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	float num = 32;

	for (int i = 0; i < num; ++i)
	{
		float t0 = i / float(num);
		float t1 = (i + 1) / float(num);

		//Vector3 bezier0 = Lerp(controlPoint0, controlPoint1, t0);
		//Vector3 bezier1 = Lerp(controlPoint1, controlPoint2, t1);

		Vector3 bezier0 = Bezier(controlPoint0, controlPoint1, controlPoint2, t0);
		Vector3 bezier1 = Bezier(controlPoint0, controlPoint1, controlPoint2, t1);

		Vector3 transform0 = Transform(bezier0, viewProjectionMatrix);
		Vector3 transform1 = Transform(bezier1, viewProjectionMatrix);

		Vector3 screenB0 = Transform(transform0, viewportMatrix);
		Vector3 screenB1 = Transform(transform1, viewportMatrix);

		Novice::DrawLine((int)screenB0.x, (int)screenB0.y, (int)screenB1.x, (int)screenB1.y, color);
	}
}

Vector3 GetWorldPosition(Matrix4x4& worldMatrix)
{
	//ワールド座標を入れる変数
	Vector3 worldPos;

	//ワールド座標の平行移動成分を取得(ワールド座標)
	worldPos.x = worldMatrix.m[3][0];
	worldPos.y = worldMatrix.m[3][1];
	worldPos.z = worldMatrix.m[3][2];

	return worldPos;
}
