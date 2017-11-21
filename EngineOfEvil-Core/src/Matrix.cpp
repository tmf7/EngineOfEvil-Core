#include "Matrix.h"

eoeMat4 mat4_identity(1.0f);
eoeMat4 mat4_zero;

//--------------------------
// eoeMat4::eoeMat4
//--------------------------
eoeMat4::eoeMat4(const float diagonal) {
	columns[0].x = 1.0f;
	columns[1].y = 1.0f;
	columns[2].z = 1.0f;
	columns[3].w = 1.0f;
}

//--------------------------
// eoeMat4::operator[]
// returns the requested column of *this
//--------------------------
eoeVec4 & eoeMat4::operator[](int column) {
	return columns[column];
}

//--------------------------
// eoeMat4::operator[]
// returns a copy of the requested column of *this
//--------------------------
eoeVec4	eoeMat4::operator[](int column) const {
	return columns[column];
}


//--------------------------
// eoeMat4::operator*
//--------------------------
eoeMat4	eoeMat4::operator*(const eoeMat4 &a) const {
	eoeMat4 result;
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			float sum = 0.0f;
			for (int index = 0; index < 4; ++index) {
				sum += columns[index][r] * a.columns[c][index];
			}
			result[c][r] = sum;
		}
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
	return columns[0].ToFloatPtr();
}

//-----------------------------------
// eoeMat4::ToFloatPtr
// returns a pointer to the first element of the matrix
//-----------------------------------
float * eoeMat4::ToFloatPtr() {
	return columns[0].ToFloatPtr();
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

	result[0].x = (1.0f / aspectRatio) * ithf;
	result[1].y = ithf;
	result[3].z = (far + near) * inmf;
	result[3].w = -1.0f;
	result[4].z = 2.0f * far * near * inmf;
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

	result[0].x = 2.0f * irml;
	result[1].y = 2.0f * itmb;
	result[3].z = -2.0f * ifmn;
	result[4].x = (right + left) * -irml;
	result[4].y = (top + bottom) * -itmb;
	result[4].z = (far + near) * -ifmn;
	result[4].w = 1.0f;
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

	result[0].x = cos + axis.x * axis.x * omc;
	result[0].y = xy * omc - axis.z * sin;
	result[0].z = xz * omc + axis.y * sin;

	result[1].x = xy * omc + axis.z * sin;
	result[1].y = cos + axis.y * axis.y * omc;
	result[1].z = yz * omc - axis.x * sin;

	result[2].x = xz * omc - axis.y * sin;
	result[2].y = yz * omc + axis.x * sin;
	result[2].z = cos + axis.z * axis.z * omc;

	result[3].w = 1.0f;
	return result;
}

//--------------------------
// eoeMat4::GetTranslation
//--------------------------
eoeMat4	eoeMat4::GetTranslation(const eoeVec3 & translation) {
	eoeMat4 result(1.0f);
	result[0].w = translation.x;
	result[1].w = translation.y;
	result[2].w = translation.z;
	return result;
}

//--------------------------
// eoeMat4::GetScale
//--------------------------
eoeMat4	eoeMat4::GetScale(const eoeVec3 & scale) {
	eoeMat4 result(1.0f);
	result[0].x = scale.x;
	result[1].y = scale.y;
	result[2].z = scale.z;
	return result;
}