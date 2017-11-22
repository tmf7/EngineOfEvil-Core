#include "Matrix.h"

eoeMat4 mat4_identity(1.0f);
eoeMat4 mat4_zero;

//--------------------------
// eoeMat4::eoeMat4
//--------------------------
eoeMat4::eoeMat4(const float diagonal) {
	matrix[0].x = 1.0f;
	matrix[1].y = 1.0f;
	matrix[2].z = 1.0f;
	matrix[3].w = 1.0f;
}

//--------------------------
// eoeMat4::operator[]
// returns the requested column of *this
//--------------------------
eoeVec4 & eoeMat4::operator[](int column) {
	return matrix[column];
}

//--------------------------
// eoeMat4::operator[]
// returns a copy of the requested column of *this
//--------------------------
eoeVec4	eoeMat4::operator[](int column) const {
	return matrix[column];
}

//--------------------------
// eoeMat4::operator*
// column-vector matrix multiplication
//--------------------------
eoeVec4	eoeMat4::operator*(const eoeVec4 &v) const {													
	return eoeVec4( matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3] * v.w,
					matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3] * v.w,
					matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3] * v.w,
					matrix[3][0] * v.x + matrix[3][1] * v.y + matrix[3][2] * v.z + matrix[3][3] * v.w );
}

//--------------------------
// eoeMat4::operator*
//--------------------------
eoeMat4	eoeMat4::operator*(const eoeMat4 &a) const {
	eoeMat4 result;
	const float * m1Ptr = reinterpret_cast<const float *>(this);	// faster than a function call to ToFloatPtr
	const float * m2Ptr = reinterpret_cast<const float *>(&a);
	float * resultPtr = reinterpret_cast<float *>(&result);

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			*resultPtr = m1Ptr[0] * m2Ptr[ 0 * 4 + c ]
					   + m1Ptr[1] * m2Ptr[ 1 * 4 + c ]
					   + m1Ptr[2] * m2Ptr[ 2 * 4 + c ]
					   + m1Ptr[3] * m2Ptr[ 3 * 4 + c ];
			++resultPtr;
		}
		m1Ptr += 4;
	}
	return result;
}

//--------------------------
// eoeMat4::operator*=
//--------------------------
eoeMat4 & eoeMat4::operator*=(const eoeMat4 &a) {
	*this = *this * a;
	return *this;
}

//-----------------------------------
// eoeMat4::ToFloatPtr
// returns a pointer to the first element of the matrix
//-----------------------------------
const float * eoeMat4::ToFloatPtr() const {
	return matrix[0].ToFloatPtr();
}

//-----------------------------------
// eoeMat4::ToFloatPtr
// returns a pointer to the first element of the matrix
//-----------------------------------
float * eoeMat4::ToFloatPtr() {
	return matrix[0].ToFloatPtr();
}

//--------------------------
// eoeMat4::GetIdentity
//--------------------------
eoeMat4 eoeMat4::GetIdentity() {
	return mat4_identity;
}

//--------------------------
// eoeMat4::GetPerspective
//--------------------------
eoeMat4	eoeMat4::GetPerspective(float fovDegrees, float aspectRatio, float near, float far) {
	eoeMat4 result;
	const float ithf = 1.0f / SDL_tanf(eoeMath::ToRadians(fovDegrees) * 0.5f);
	const float inmf = 1.0f / (near - far);

	result[0][0] = (1.0f / aspectRatio) * ithf;
	result[1][1] = ithf;
	result[2][2] = (far + near) * inmf;
	result[3][2] = -1.0f;
	result[2][3] = 2.0f * far * near * inmf;
	return result;
}

//--------------------------
// eoeMat4::GetOrthographic
//--------------------------
eoeMat4	eoeMat4::GetOrthographic(float left, float right, float bottom, float top, float near, float far) {
	eoeMat4 result;
	const float irml = 1.0f / (right - left);
	const float itmb = 1.0f / (top - bottom);
	const float ifmn = 1.0f / (far - near);

	result[0][0] = 2.0f * irml;
	result[1][1] = 2.0f * itmb;
	result[2][2] = -2.0f * ifmn;
	result[0][3] = (right + left) * -irml;
	result[1][3] = (top + bottom) * -itmb;
	result[2][3] = (far + near) * -ifmn;
	result[3][3] = 1.0f;
	return result;
}

//--------------------------
// eoeMat4::GetRotation
//--------------------------
eoeMat4	eoeMat4::GetRotation(const eoeVec3 & axis, float angleDegrees) {
	eoeMat4 result;
	const float angleRads = eoeMath::ToRadians(angleDegrees);
	const float cos = SDL_cosf(angleRads);
	const float sin = SDL_sinf(angleRads);
	const float omc = 1.0f - cos;
	const float xy = axis.x * axis.y;
	const float xz = axis.x * axis.z;
	const float yz = axis.y * axis.z;

	result[0][0] = cos + axis.x * axis.x * omc;
	result[0][1] = xy * omc - axis.z * sin;
	result[0][2] = xz * omc + axis.y * sin;

	result[1][0] = xy * omc + axis.z * sin;
	result[1][1] = cos + axis.y * axis.y * omc;
	result[1][2] = yz * omc - axis.x * sin;

	result[2][0] = xz * omc - axis.y * sin;
	result[2][1] = yz * omc + axis.x * sin;
	result[2][2] = cos + axis.z * axis.z * omc;

	result[3].w = 1.0f;
	return result;
}

//--------------------------
// eoeMat4::GetTranslation
//--------------------------
eoeMat4	eoeMat4::GetTranslation(const eoeVec3 & translation) {
	eoeMat4 result(1.0f);
	result[0][3]= translation.x;
	result[1][3]= translation.y;
	result[2][3]= translation.z;
	return result;
}

//--------------------------
// eoeMat4::GetScale
//--------------------------
eoeMat4	eoeMat4::GetScale(const eoeVec3 & scale) {
	eoeMat4 result(1.0f);
	result[0][0]= scale.x;
	result[1][1] = scale.y;
	result[2][2] = scale.z;
	return result;
}