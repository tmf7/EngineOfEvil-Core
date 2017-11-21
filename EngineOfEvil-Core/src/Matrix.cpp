#include "Matrix.h"

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
// eoeMat4::GetData
// returns a pointer to the first element of the matrix
//-----------------------------------
float * eoeMat4::GetData() {
	return &columns[0][0];
}

//--------------------------
// eoeMat4::GetIdentity
//--------------------------
eoeMat4 eoeMat4::GetIdentity() {
	return eoeMat4(1.0f);
}

//--------------------------
// eoeMat4::GetPerspective
//--------------------------
eoeMat4	eoeMat4::GetPerspective(float fov, float aspectRatio, float near, float far) {

}

//--------------------------
// eoeMat4::GetOrthographic
//--------------------------
eoeMat4	eoeMat4::GetOrthographic(float left, float right, float bottom, float top, float near, float far) {

}

//--------------------------
// eoeMat4::GetRotation
//--------------------------
eoeMat4	eoeMat4::GetRotation(const eoeVec3 & axis, float degrees) {

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