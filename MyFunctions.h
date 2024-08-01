#pragma once
#include <cassert>
#include <cmath>

static const int kWindowWidth = 1280;
static const int kWindowHeight = 720;

/// \brief 3次元ベクトル
struct Vector3
{
	float x;
	float y;
	float z;

	//オペレータ
	Vector3 operator+(const Vector3& other)const { return { x + other.x, y + other.y, z + other.z }; }
	Vector3& operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3 operator-(const Vector3& other)const { return { x - other.x, y - other.y, z - other.z }; }
	Vector3& operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3 operator*(float scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}
	Vector3 operator/(float scalar) const {
		// スカラーがゼロでないことを確認する（ゼロ除算を避ける）
		assert(scalar != 0 && "Division by zero!");
		return Vector3(x / scalar, y / scalar, z / scalar);
	}
};

/// \brief 4x4の行列
struct Matrix4x4
{
	float m[4][4];
};

/// \brief 球
struct Sphere
{
	Vector3 center;//!<中心点
	float radius;  //!<半径
	uint32_t color;//色
};

/// \brief 直線
struct Line
{
	Vector3 origin;		//始点
	Vector3 diff;		//終点への差分ベクトル
};

/// \brief 半直線
struct Ray
{
	Vector3 origin;		//始点
	Vector3 diff;		//終点への差分ベクトル
};

/// \brief 線分
struct Segment
{
	Vector3 origin;		//始点
	Vector3 diff;		//終点への差分ベクトル
	uint32_t color;		//色
};

struct Triangle
{
	Vector3 vertices[3]; //!< 頂点
};

struct AABB
{
	Vector3 min;//!<最小点
	Vector3 max;//!< 最大点
};

struct Spring
{
	Vector3 anchor;           // アンカー。固定された端の位置
	float naturalLength;      // 自然長
	float stiffness;          // 剛性。バネ定数k
	float dampingCoefficient; // 減衰係数
};

struct Ball
{
	Vector3 position;     // ボールの位置
	Vector3 velocity;     // ボールの速度
	Vector3 acceleration; // ボールの加速度
	float mass;           // ボールの質量
	float radius;         // ボールの半径
	unsigned int color;   // ボールの色
};


//=======================================================================
//							Matrix4x4
//=======================================================================

/// \brief 4x4行列の和
/// \param m1 
/// \param m2 
/// \return 
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

/// \brief 4x4行列の差
/// \param m1 
/// \param m2 
/// \return 
Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2);

/// \brief 4x4行列の積
/// \param m1 
/// \param m2 
/// \return 
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

/// \brief 4x4行列のクロス積
/// \param v1 
/// \param v2 
/// \return 
Vector3 Cross(const Vector3& v1, const Vector3& v2);

/// \brief 逆行列
/// \param m 
/// \return 
Matrix4x4 Inverse(const Matrix4x4& m);

/// \brief 転置行列
/// \param m 
/// \return 
Matrix4x4 Transpose(const Matrix4x4& m);



/// \brief x軸回転行列
/// \param radian 
/// \return 
Matrix4x4 MakeRotateXMatrix(float radian);
/// \brief y軸回転行列
/// \param radian 
/// \return 
Matrix4x4 MakeRotateYMatrix(float radian);
/// \brief z軸回転行列
/// \param radian 
/// \return 
Matrix4x4 MakeRotateZMatrix(float radian);

/// \brief 座標変換
/// \param vector 
/// \param matrix 
/// \return 
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

/// \brief アフィン変換
/// \param scale 拡大縮小
/// \param rotate 回転
/// \param translate 平行移動
/// \return 
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

/// \brief 透視投影行列
/// \param fovY 
/// \param aspectRatio 
/// \param nearClip 
/// \param farClip 
/// \return 
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

/// \brief 正射影行列
/// \param left 
/// \param top 
/// \param right 
/// \param bottom 
/// \param nearClip 
/// \param farClip 
/// \return 
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

/// \brief ビューポート変換行列
/// \param left 
/// \param top 
/// \param width 
/// \param height 
/// \param minDepth 
/// \param maxDepth 
/// \return 
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);


static const int kRowHeight = 20;
static const int kColumnWidth = 60;
/// \brief 4x4行列の出力
/// \param x 
/// \param y 
/// \param matrix 
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);

//=======================================================================
//							Vector3
//=======================================================================

float Length(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

/// \brief スカラー倍
/// \param scalar 
/// \param v 
/// \return 
Vector3 Multiply(float scalar, const Vector3& v);

/// \brief 内積
/// \param v1 
/// \param v2 
/// \return 
float Dot(Vector3 v1, Vector3 v2);

/// \brief 正規化
/// \param v 
/// \return 
Vector3 Normalize(const Vector3& v);

/// \brief Vector3の出力
/// \param x 
/// \param y 
/// \param vector 
/// \param label 
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);


/// \brief グリッドの描画
/// \param viewProjectionMatrix 
/// \param viewportMatrix 
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// \brief 球の描画
/// \param sphere 
/// \param viewProjectionMatrix 
/// \param viewportMatrix 
/// \param color 
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// \brief 正射影ベクトル
/// \param v1 
/// \param v2 
/// \return 
Vector3 Project(const Vector3& v1, const Vector3& v2);

/// \brief 最近接点
/// \param point 
/// \param segment 
/// \return 
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);


/// \brief 球と球の衝突判定
/// \param s1 
/// \param s2 
/// \return 
bool IsCollision(const Sphere& s1, const Sphere& s2);


struct Plane
{
	Vector3 normal; // !< 法線
	float distance; // !< 距離
};

/// \brief 平面の描画
/// \param vector 
/// \return 
Vector3 Perpendicular(const Vector3& vector);

/// \brief 球と平面の衝突判定
/// \param sphere 
/// \param plane 
/// \return 
bool IsCollision(const Sphere& sphere, const Plane& plane);


void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

bool isColision(const Segment& segment, const Plane& plane);

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

bool isCollision(const Segment& segment, const Triangle& triangle);

//AABB・AABB
bool isCollision(const AABB& aabb1, const AABB& aabb2);

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

bool isCollision(const AABB& aabb, const Sphere& sphere);

bool isCollision(const AABB& aabb, const Segment segment);

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

Vector3 GetWorldPosition(Matrix4x4& worldMatrix);
