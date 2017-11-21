#ifndef EOECORE_MATRIX_H
#define EOECORE_MATRIX_H

#include "Vector.h"

//-----------------------------------
//			eoeMat4
//	 4x4 row-major matrix
//  default ctor is all zeros
// TODO: model matrix (conversion from modelspace to worldspace) == (translation * rotation * scale), then  * modelCoordinate to get the new worldspace coordinate
// TODO: camera matrix (translation * rotation) ?
// TODO: projection (ortho/perspective) done, but needs double checking
//-----------------------------------
class eoeMat4 {
public:

	eoeVec4						columns[4];

								eoeMat4() = default;
	explicit					eoeMat4(const float diagonal);

	eoeVec4 &					operator[](int column);
	eoeVec4						operator[](int column) const;
	eoeMat4						operator*(const eoeMat4 &a) const;
	eoeMat4 &					operator*=(const eoeMat4 &a);

	const float *				ToFloatPtr() const;
	float *						ToFloatPtr();

	static eoeMat4				GetIdentity();
	static eoeMat4				GetPerspective(float fov, float aspectRatio, float near, float far);
	static eoeMat4				GetOrthographic(float left, float right, float bottom, float top, float near, float far);	
	static eoeMat4				GetRotation(const eoeVec3 & axis, float degrees);
	static eoeMat4				GetTranslation(const eoeVec3 & translation);
	static eoeMat4				GetScale(const eoeVec3 & scale);
};

extern eoeMat4 mat4_identity;
extern eoeMat4 mat4_zero;

#endif /* EOECORE_MATRIX_H */