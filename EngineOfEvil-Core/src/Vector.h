#ifndef EOECORE_VECTOR_H
#define EOECORE_VECTOR_H

#include <float.h>
#include "SDL.h"			// for SDL_sqrtf
#include "Math.h"

// handles direction vectors, quaternions, and their operations
// as well as a 4-float position vector

//--------------------------------------------
//
//
//					eoeVec2
//		--direction vector behavior--
//
//
//--------------------------------------------
class eoeVec2 {
public:

	float			x = 0.0f;
	float			y = 0.0f;

					eoeVec2() = default;
	explicit		eoeVec2(const float x, const float y);

	void			Set(const float x, const float y);
	void			Zero();
	float			Normalize();
	eoeVec2			Normalized();
	float			Length() const;
	float			LengthSquared() const;

	float			operator[](const int index) const;
	float &			operator[](const int index);
	eoeVec2			operator-() const;
	float			operator*(const eoeVec2 &a) const;
	eoeVec2			operator*(const float a) const;
	eoeVec2			operator/(const float a) const;
	eoeVec2			operator+(const eoeVec2 &a) const;
	eoeVec2			operator-(const eoeVec2 &a) const;
	eoeVec2 &		operator+=(const eoeVec2 &a);
	eoeVec2 &		operator-=(const eoeVec2 &a);
	eoeVec2 &		operator/=(const float a);
	eoeVec2 &		operator*=(const float a);

	bool			Compare(const eoeVec2 &a) const;
	bool			Compare(const eoeVec2 &a, const float epsilon) const;
	bool			operator==(const eoeVec2 &a) const;
	bool			operator!=(const eoeVec2 &a) const;

	void			SnapInt();
};

extern eoeVec2 vec2_zero;
extern eoeVec2 vec2_oneZero;
extern eoeVec2 vec2_zeroOne;
extern eoeVec2 vec2_one;
extern eoeVec2 vec2_epsilon;

//-------------------------
// eoeVec2::eoeVec2
//-------------------------
inline eoeVec2::eoeVec2(const float x, const float y) 
	: x(x),
	  y(y) {
}

//-------------------------
// eoeVec2::Set
// modifies the current x and y values
//-------------------------
inline void eoeVec2::Set(const float x, const float y) {
	this->x = x;
	this->y = y;
}

//-------------------------
// eoeVec2::Zero
// sets x and y to zero
//-------------------------
inline void eoeVec2::Zero() {
	x = 0.0f;
	y = 0.0f;
}

//-------------------------
// eoeVec2::Compare
// returns true for exact x,y match
//-------------------------
inline bool eoeVec2::Compare(const eoeVec2 &a) const {
	return ((x == a.x) && (y == a.y));
}

//-------------------------
// eoeVec2::Compare
// returns true for x,y match within range of epsilon
//-------------------------
inline bool eoeVec2::Compare(const eoeVec2 &a, const float epsilon) const {
	if ( SDL_fabs(x - a.x) > epsilon)
		return false;

	if (SDL_fabs(y - a.y) > epsilon)
		return false;

	return true;
}

//-------------------------
// eoeVec2::operator[]
// returns x for [0] and y for [1]
// undefined behavior for index out of bounds
//-------------------------
inline float eoeVec2::operator[](const int index) const {
	return (&x)[index];
}

//-------------------------
// eoeVec2::operator[]
// returns x for [0] and y for [1]
// undefined behavior for index out of bounds
//-------------------------
inline float & eoeVec2::operator[](const int index) {
	return (&x)[index];
}

//-------------------------
// eoeVec2::operator==
// returns the result of Compare without epsilon
//-------------------------
inline bool eoeVec2::operator==(const eoeVec2 &a) const {
	return Compare(a);
}

//-------------------------
// eoeVec2::operator!=
// returns the negated result of Compare without epsilon
//-------------------------
inline bool eoeVec2::operator!=(const eoeVec2 &a) const {
	return !Compare(a);
}

//-------------------------
// eoeVec2::Length
// returns vector length
//-------------------------
inline float eoeVec2::Length() const {
	return SDL_sqrtf(x * x + y * y);
}

//-------------------------
// eoeVec2::LengthSquared
// returns vector length squared
//-------------------------
inline float eoeVec2::LengthSquared() const {
	return (x * x + y * y);
}

//-------------------------
// eoeVec2::Normalize
// scales internal x,y to unit length vector
// returns normalized length of 0 or 1
//-------------------------
inline float eoeVec2::Normalize() {
	float sqrLength, invLength;

	sqrLength = x * x + y * y;
	sqrLength = SDL_sqrtf(sqrLength);

	if (sqrLength == 0)
		invLength = 0;
	else
		invLength = 1.0f / sqrLength;

	x *= invLength;
	y *= invLength;
	return invLength * sqrLength;
}

//-------------------------
// eoeVec2::Normalized
// scales a copy of x,y to unit length vector
//-------------------------
inline eoeVec2 eoeVec2::Normalized() {
	float sqrLength;
	float invLength;

	sqrLength = x * x + y * y;
	sqrLength = SDL_sqrtf(sqrLength);

	if (sqrLength == 0)
		invLength = 0;
	else
		invLength = 1.0f / sqrLength;

	return eoeVec2(x * invLength, y * invLength);
}

//-------------------------
// eoeVec2::operator-
// returns eoeVec2 with negated x and y
//-------------------------
inline eoeVec2 eoeVec2::operator-() const {
	return eoeVec2(-x, -y);
}

//-------------------------
// eoeVec2::operator-
// returns an eoeVec2 using the difference between two vectors' x and y
//-------------------------
inline eoeVec2 eoeVec2::operator-(const eoeVec2 &a) const {
	return eoeVec2(x - a.x, y - a.y);
}

//-------------------------
// eoeVec2::operator*
// returns the dot product of two eoeVec2s
//-------------------------
inline float eoeVec2::operator*(const eoeVec2 &a) const {
	return x * a.x + y * a.y;
}

//-------------------------
// eoeVec2::operator*
// returns an eoeVec2 with x and y scaled by a
//-------------------------
inline eoeVec2 eoeVec2::operator*(const float a) const {
	return eoeVec2(x * a, y * a);
}

//-------------------------
// eoeVec2::operator/
// returns an eoeVec2 with de-scaled x and y by a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec2 eoeVec2::operator/(const float a) const {
	float inva = 1.0f / a;
	return eoeVec2(x * inva, y * inva);
}

//-------------------------
// eoeVec2::operator+
// returns an eoeVec2 using the sum of two eoeVec2's x and y
//-------------------------
inline eoeVec2 eoeVec2::operator+(const eoeVec2 &a) const {
	return eoeVec2(x + a.x, y + a.y);
}

//-------------------------
// eoeVec2::operator+=
// returns this with x and y added to an eoeVec2's x and y
//-------------------------
inline eoeVec2 & eoeVec2::operator+=(const eoeVec2 &a) {
	x += a.x;
	y += a.y;
	return *this;
}

//-------------------------
// eoeVec2::operator/=
// returns this with x and y de-scaled by a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec2 & eoeVec2::operator/=(const float a) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	return *this;
}

//-------------------------
// eoeVec2::operator-=
// returns this with x and y subtracted by another eoeVec2's x and y
//-------------------------
inline eoeVec2 & eoeVec2::operator-=(const eoeVec2 &a) {
	x -= a.x;
	y -= a.y;
	return *this;
}

//-------------------------
// eoeVec2::operator*=
// returns this with x and y scaled by a
//-------------------------
inline eoeVec2 & eoeVec2::operator*=(const float a) {
	x *= a;
	y *= a;
	return *this;
}

//-------------------------
// eoeVec2::SnapInt
// moves x and y to the nearest integer value
//-------------------------
inline void eoeVec2::SnapInt() {
	x = floorf(x + 0.5f);
	y = floorf(y + 0.5f);
}

//--------------------------------------------
//
//
//				eoeVec3
//	  --direction vector behavior--
//
//
//--------------------------------------------
class eoeVec3 {
public:

	float			x = 0.0f;
	float			y = 0.0f;
	float			z = 0.0f;

					eoeVec3() = default;
	explicit		eoeVec3(const float x, const float y, const float z);
					eoeVec3(const eoeVec2 & point);

	void			Set(const float x, const float y, const float z);
	void			Zero();
	float			Normalize();
	float			Length() const;
	float			LengthSquared() const;

	float			operator[](const int index) const;
	float &			operator[](const int index);
	eoeVec3			operator-() const;
	float			operator*(const eoeVec3 &a) const;
	eoeVec3			operator*(const float a) const;
	eoeVec3			operator/(const float a) const;
	eoeVec3			operator+(const eoeVec3 &a) const;
	eoeVec3			operator-(const eoeVec3 &a) const;
	eoeVec3 &		operator+=(const eoeVec3 &a);
	eoeVec3 &		operator-=(const eoeVec3 &a);
	eoeVec3 &		operator/=(const float a);
	eoeVec3 &		operator*=(const float a);	

	bool			Compare(const eoeVec3 &a) const;
	bool			Compare(const eoeVec3 &a, const float epsilon) const;
	bool			operator==(const eoeVec3 &a) const;
	bool			operator!=(const eoeVec3 &a) const;

	eoeVec3			Cross(const eoeVec3 &a) const;
	eoeVec3 &		Cross(const eoeVec3 &a, const eoeVec3 &b);

	void			SnapInt();
};

extern eoeVec3 vec3_right;
extern eoeVec3 vec3_left;
extern eoeVec3 vec3_up;
extern eoeVec3 vec3_down;
extern eoeVec3 vec3_forward;
extern eoeVec3 vec3_back;
extern eoeVec3 vec3_zero;
extern eoeVec3 vec3_one;

//-------------------------
// eoeVec3::eoeVec3
//-------------------------
inline eoeVec3::eoeVec3(const float x, const float y, const float z)
	: x(x),
	  y(y),
	  z(z) {
}

//-------------------------
// eoeVec3::eoeVec3
//-------------------------
inline eoeVec3::eoeVec3(const eoeVec2 & point)
	: x(point.x),
	  y(point.y),
	  z(0.0f) {
}

//-------------------------
// eoeVec3::Set
// modifies the current x, y, and z values
//-------------------------
inline void eoeVec3::Set(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

//-------------------------
// eoeVec3::Zero
// sets x, y, and z to zero
//-------------------------
inline void eoeVec3::Zero() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

//-------------------------
// eoeVec3::Compare
// returns true for exact x,y,z match
//-------------------------
inline bool eoeVec3::Compare(const eoeVec3 &a) const {
	return ((x == a.x) && (y == a.y) && (z == a.z));
}

//-------------------------
// eoeVec3::Compare
// returns true for x,y,z match within range of epsilon
//-------------------------
inline bool eoeVec3::Compare(const eoeVec3 &a, const float epsilon) const {

	if (SDL_fabs(x - a.x) > epsilon)
		return false;

	if (SDL_fabs(y - a.y) > epsilon)
		return false;

	if (SDL_fabs(z - a.z) > epsilon)
		return false;

	return true;
}

//-------------------------
// eoeVec3::operator[]
// returns x for [0], y for [1], and z for [2]
// undefined behavior for index out of bounds
//-------------------------
inline float eoeVec3::operator[](const int index) const {
	return (&x)[index];
}

//-------------------------
// eoeVec3::operator[]
// returns x for [0], y for [1], and z for [2]
// undefined behavior for index out of bounds
//-------------------------
inline float & eoeVec3::operator[](const int index) {
	return (&x)[index];
}

//-------------------------
// eoeVec3::operator==
// returns the result of Compare without epsilon
//-------------------------
inline bool eoeVec3::operator==(const eoeVec3 &a) const {
	return Compare(a);
}

//-------------------------
// eoeVec3::operator!=
// returns the negated result of Compare without epsilon
//-------------------------
inline bool eoeVec3::operator!=(const eoeVec3 &a) const {
	return !Compare(a);
}

//-------------------------
// eoeVec3::Length
// returns vector length
//-------------------------
inline float eoeVec3::Length() const {
	return SDL_sqrtf(x * x + y * y + z * z);
}

//-------------------------
// eoeVec3::LengthSquared
// returns vector length squared
//-------------------------
inline float eoeVec3::LengthSquared() const {
	return (x * x + y * y + z * z);
}

//-------------------------
// eoeVec3::Normalize
// scales internal x,y, and z to unit length vector
// returns normalized length of 0 or 1
//-------------------------
inline float eoeVec3::Normalize() {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z;
	sqrLength = SDL_sqrtf(sqrLength);

	if (sqrLength == 0)
		invLength = 0;
	else
		invLength = 1.0f / sqrLength;

	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

//-------------------------
// eoeVec3::operator-
// returns eoeVec3 with negated x, y, and z
//-------------------------
inline eoeVec3 eoeVec3::operator-() const {
	return eoeVec3(-x, -y, -z);
}

//-------------------------
// eoeVec3::operator-
// returns an eoeVec3 using the difference between two vectors' x, y, and z
//-------------------------
inline eoeVec3 eoeVec3::operator-(const eoeVec3 &a) const {
	return eoeVec3(x - a.x, y - a.y, z - a.z);
}

//-------------------------
// eoeVec3::operator*
// returns the dot product of two eoeVec3s
//-------------------------
inline float eoeVec3::operator*(const eoeVec3 &a) const {
	return x * a.x + y * a.y + z * a.z;
}

//-------------------------
// eoeVec3::operator*
// returns an eoeVec3 with x, y, and z scaled by a
//-------------------------
inline eoeVec3 eoeVec3::operator*(const float a) const {
	return eoeVec3(x * a, y * a, z * a);
}

//-------------------------
// eoeVec3::operator/
// returns an eoeVec3 with de-scaled x, y, and z by a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec3 eoeVec3::operator/(const float a) const {
	float inva = 1.0f / a;
	return eoeVec3(x * inva, y * inva, z * inva);
}

//-------------------------
// eoeVec3::operator+
// returns an eoeVec3 using the sum of two eoeVec3's x, y, and z
//-------------------------
inline eoeVec3 eoeVec3::operator+(const eoeVec3 &a) const {
	return eoeVec3(x + a.x, y + a.y, z + a.z);
}

//-------------------------
// eoeVec3::operator+=
// returns this with x, y, and z added to an eoeVec3's x, y, and z
//-------------------------
inline eoeVec3 & eoeVec3::operator+=(const eoeVec3 &a) {
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}

//-------------------------
// eoeVec3::operator/=
// returns this with x, y, and z de-scaled by a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec3 & eoeVec3::operator/=(const float a) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;
	return *this;
}

//-------------------------
// eoeVec3::operator-=
// returns this with x, y, and z subtracted by another eoeVec3's x, y, and z
//-------------------------
inline eoeVec3 & eoeVec3::operator-=(const eoeVec3 &a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}

//-------------------------
// eoeVec3::operator*=
// returns this with x, y, and z scaled by a
//-------------------------
inline eoeVec3 & eoeVec3::operator*=(const float a) {
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

//-------------------------
// eoeVec3::Cross
// returns the an eoeVec3 that is the cross product of *this with another eoeVec3
//-------------------------
inline eoeVec3 eoeVec3::Cross(const eoeVec3 &a) const {
	return eoeVec3( y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
}

//-------------------------
// eoeVec3::Cross
// sets *this to the cross product of two eoeVec3s
//-------------------------
inline eoeVec3 & eoeVec3::Cross(const eoeVec3 &a, const eoeVec3 &b) {
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return *this;
}

//-------------------------
// eoeVec3::SnapInt
// moves x, y, and z to the nearest integer value
//-------------------------
inline void eoeVec3::SnapInt() {
	x = floorf(x + 0.5f);
	y = floorf(y + 0.5f);
	z = floorf(z + 0.5f);
}


//--------------------------------------------
//
//
//					eoeVec4
//		--position vector behavior--
//
//
//--------------------------------------------
class eoeVec4 {
public:

	float				x = 0.0f;
	float				y = 0.0f;
	float				z = 0.0f;
	float				w = 0.0f;

						eoeVec4() = default;
						eoeVec4(const float x, const float y, const float z, const float w);

	void				Set(const float x, const float y, const float z, const float w);
	void				Zero();
	void				Clamp01();

	float				operator[](const int index) const;
	float &				operator[](const int index);
	eoeVec4				operator-() const;
	eoeVec4				operator*(const eoeVec4 &a) const;
	eoeVec4				operator*(const float a) const;
	eoeVec4				operator/(const eoeVec4 &a) const;
	eoeVec4				operator/(const float a) const;
	eoeVec4				operator+(const eoeVec4 &a) const;
	eoeVec4				operator-(const eoeVec4 &a) const;
	eoeVec4 &			operator+=(const eoeVec4 &a);
	eoeVec4 &			operator-=(const eoeVec4 &a);
	eoeVec4 &			operator/=(const eoeVec4 &a);
	eoeVec4 &			operator/=(const float a);
	eoeVec4 &			operator*=(const eoeVec4 &a);
	eoeVec4 &			operator*=(const float a);	

	bool				Compare(const eoeVec4 &a) const;
	bool				Compare(const eoeVec4 &a, const float epsilon) const;
	bool				operator==(const eoeVec4 &a) const;
	bool				operator!=(const eoeVec4 &a) const;

	void				SnapInt();
};

//-------------------------
// eoeVec4::eoeVec4
//-------------------------
inline eoeVec4::eoeVec4(const float x, const float y, const float z, const float w)
	: x(x),
	  y(y),
	  z(z),
	  w(w) {
}

//-------------------------
// eoeVec4::Set
// modifies the current x, y, z, and w values
//-------------------------
inline void eoeVec4::Set(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//-------------------------
// eoeVec4::Zero
// sets x, y, z, and w to zero
//-------------------------
inline void eoeVec4::Zero() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

//-------------------------
// eoeVec4::Compare
// returns true for exact x,y,z,w match
//-------------------------
inline bool eoeVec4::Compare(const eoeVec4 &a) const {
	return ((x == a.x) && (y == a.y) && (z == a.z) && (w == a.w));
}

//-------------------------
// eoeVec4::Compare
// returns true for x,y,z,w match within range of epsilon
//-------------------------
inline bool eoeVec4::Compare(const eoeVec4 &a, const float epsilon) const {

	if (SDL_fabs(x - a.x) > epsilon)
		return false;

	if (SDL_fabs(y - a.y) > epsilon)
		return false;

	if (SDL_fabs(z - a.z) > epsilon)
		return false;

	if (SDL_fabs(w - a.w) > epsilon)
		return false;

	return true;
}

//-------------------------
// eoeVec4::operator[]
// returns x for [0], y for [1], z for [2], and w for [3]
// undefined behavior for index out of bounds
//-------------------------
inline float eoeVec4::operator[](const int index) const {
	return (&x)[index];
}

//-------------------------
// eoeVec4::operator[]
// returns x for [0], y for [1], z for [2], and w for [3]
// undefined behavior for index out of bounds
//-------------------------
inline float & eoeVec4::operator[](const int index) {
	return (&x)[index];
}

//-------------------------
// eoeVec4::operator==
// returns the result of Compare without epsilon
//-------------------------
inline bool eoeVec4::operator==(const eoeVec4 &a) const {
	return Compare(a);
}

//-------------------------
// eoeVec4::operator!=
// returns the negated result of Compare without epsilon
//-------------------------
inline bool eoeVec4::operator!=(const eoeVec4 &a) const {
	return !Compare(a);
}

//-------------------------
// eoeVec4::Clamp01
// clamps x,y,z,w into range [0,1]
//-------------------------
inline void eoeVec4::Clamp01() {
	x = x < 0.0f ? 0.0f : (x > 1.0f ? 1.0f : x);
	y = y < 0.0f ? 0.0f : (y > 1.0f ? 1.0f : y);
	z = z < 0.0f ? 0.0f : (z > 1.0f ? 1.0f : z);
	w = w < 0.0f ? 0.0f : (w > 1.0f ? 1.0f : w);
}

//-------------------------
// eoeVec4::operator-
// returns eoeVec4 with negated x, y, and z
//-------------------------
inline eoeVec4 eoeVec4::operator-() const {
	return eoeVec4(-x, -y, -z, -w);
}

//-------------------------
// eoeVec4::operator-
// returns an eoeVec4 using the difference between two vectors' x, y, z, w
//-------------------------
inline eoeVec4 eoeVec4::operator-(const eoeVec4 &a) const {
	return eoeVec4(x - a.x, y - a.y, z - a.z, w - a.w);
}

//-------------------------
// eoeVec4::operator*
// scaled each component of *this using param a
//-------------------------
inline eoeVec4 eoeVec4::operator*(const eoeVec4 &a) const {
	return eoeVec4(x * a.x, y * a.y, z * a.z, w * a.w);
}

//-------------------------
// eoeVec4::operator*
// returns an eoeVec4 with x, y, z, and w scaled by a
//-------------------------
inline eoeVec4 eoeVec4::operator*(const float a) const {
	return eoeVec4(x * a, y * a, z * a, w * a);
}

//-------------------------
// eoeVec4::operator/
// returns an eoeVec4 with de-scaled x, y, z, and w by param a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec4 eoeVec4::operator/(const eoeVec4 &a) const {
	return eoeVec4(x / a.x, y / a.y, z / a.z, w / a.w);
}

//-------------------------
// eoeVec4::operator/
// returns an eoeVec4 with de-scaled x, y, z, and w by param a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec4 eoeVec4::operator/(const float a) const {
	float inva = 1.0f / a;
	return eoeVec4(x * inva, y * inva, z * inva, w * inva);
}

//-------------------------
// eoeVec4::operator+
// returns an eoeVec4 using the sum of two eoeVec4's x, y, z, and w
//-------------------------
inline eoeVec4 eoeVec4::operator+(const eoeVec4 &a) const {
	return eoeVec4(x + a.x, y + a.y, z + a.z, w + a.w);
}

//-------------------------
// eoeVec4::operator+=
// returns this with x, y, z, and w added with those of param a
//-------------------------
inline eoeVec4 & eoeVec4::operator+=(const eoeVec4 &a) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;
	return *this;
}

//-------------------------
// eoeVec4::operator/=
// returns this with x, y, z, and w de-scaled by a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec4 & eoeVec4::operator/=(const eoeVec4 &a) {
	x /= a.x;
	y /= a.y;
	z /= a.z;
	w /= a.w;
	return *this;
}

//-------------------------
// eoeVec4::operator/=
// returns this with x, y, z, and w de-scaled by a
// DEBUG: allows divide by zero errors to occur
//-------------------------
inline eoeVec4 & eoeVec4::operator/=(const float a) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;
	w *= inva;
	return *this;
}

//-------------------------
// eoeVec4::operator-=
// returns this with x, y, z, and w subtracted by those of param a
//-------------------------
inline eoeVec4 & eoeVec4::operator-=(const eoeVec4 &a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;
	return *this;
}

//-------------------------
// eoeVec4::operator*=
// returns this with x, y, z, and w scaled by those of param a
//-------------------------
inline eoeVec4 & eoeVec4::operator*=(const eoeVec4 &a) {
	x *= a.x;
	y *= a.y;
	z *= a.z;
	w *= a.w;
	return *this;
}

//-------------------------
// eoeVec4::operator*=
// returns this with x, y, z, and w scaled by a
//-------------------------
inline eoeVec4 & eoeVec4::operator*=(const float a) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;
	return *this;
}

//-------------------------
// eoeVec4::SnapInt
// moves x, y, z, and w to the nearest integer value
//-------------------------
inline void eoeVec4::SnapInt() {
	x = floorf(x + 0.5f);
	y = floorf(y + 0.5f);
	z = floorf(z + 0.5f);
	w = floorf(w + 0.5f);
}

//--------------------------------------------
//
//
//					eoeQuat
// --only deals with unit length quaternions--
//			used for quick rotations
//
//--------------------------------------------
class eoeQuat {
public:

	float				x = 0.0f;
	float				y = 0.0f;
	float				z = 0.0f;
	float				w = 0.0f;

						eoeQuat() = default;
	explicit			eoeQuat(const float x, const float y, const float z, const float w);
	explicit			eoeQuat(const eoeVec3 vector, const float scalar);

	eoeQuat				Inverse() const;
	void				Set(const float x, const float y, const float z, const float w);

	float				operator[](const int index) const;
	float &				operator[](const int index);
	eoeQuat				operator*(const eoeQuat &a) const;
	eoeVec3				operator*(const eoeVec3 &a) const;
	eoeVec2				operator*(const eoeVec2 &a) const;
	eoeQuat &			operator*=(const eoeQuat &a);

	static eoeVec3		Rotate(const eoeVec3 & rotationAxis, float degrees, const eoeVec3 & toRotate);
	static eoeVec2		Rotate(const eoeVec3 & rotationAxis, float degrees, const eoeVec2 & toRotate);
	static void			Rotate(const eoeVec3 & rotationAxis, float degrees, eoeVec3 & toRotate);
	static void			Rotate(const eoeVec3 & rotationAxis, float degrees, eoeVec2 & toRotate);
};

//-------------------------
// eoeQuat::eoeQuat
//-------------------------
inline eoeQuat::eoeQuat(const float x, const float y, const float z, const float w)
	: x(x),
	  y(y),
	  z(z),
	  w(w) {
}

//-------------------------
// eoeQuat::eoeQuat
//-------------------------
inline eoeQuat::eoeQuat(const eoeVec3 vector, const float scalar)
	: x(vector.x),
	  y(vector.y),
	  z(vector.z),
	  w(scalar) {
}

//-------------------------
// eoeQuat::operator[]
// returns x for [0], y for [1], z for [2], and w for [3]
// undefined behavior for index out of bounds
//-------------------------
inline float eoeQuat::operator[](const int index) const {
	return (&x)[index];
}

//-------------------------
// eoeQuat::operator[]
// returns x for [0], y for [1], z for [2], and w for [3]
// undefined behavior for index out of bounds
//-------------------------
inline float & eoeQuat::operator[](const int index) {
	return (&x)[index];
}

//-------------------------
// eoeQuat::operator*
// returns an eoeQuat set to the Grassman product of *this with another eoeQuat
// this*a = q*p = [ (qs*pv + ps*qv + qv X pv) (qs*ps - qv.pv) ]
//-------------------------
inline eoeQuat eoeQuat::operator*(const eoeQuat &a) const {
	return eoeQuat(w*a.x + x*a.w + y*a.z - z*a.y,
				 w*a.y + y*a.w + z*a.x - x*a.z,
				 w*a.z + z*a.w + x*a.y - y*a.x,
				 w*a.w - x*a.x - y*a.y - z*a.z);
}

//-------------------------
// eoeQuat::operator*=
// returns *this set to the Grassman product of *this with another eoeQuat
// this*a = q*p = [ (qs*pv + ps*qv + qv X pv) (qs*ps - qv.pv) ]
//-------------------------
inline eoeQuat & eoeQuat::operator*=(const eoeQuat &a) {
	*this = *this * a;
	return *this;
}

//-------------------------
// eoeQuat::operator*
// expanded and factored version of:
// (*this) * eoeQuat( a.x, a.y, a.z, 0.0f ) * (*this)^-1
// returns an eoeVec3 by rotating the given eoeVec3 
// counter-clockwise using *this eoeQuat.
// assumes a right-handed coordinate system
// --only deals with unit length quaternions--
//-------------------------
inline eoeVec3 eoeQuat::operator*(const eoeVec3 &a) const {
	float xxzz = x*x - z*z;
	float wwyy = w*w - y*y;

	float xw2 = x*w*2.0f;
	float xy2 = x*y*2.0f;
	float xz2 = x*z*2.0f;
	float yw2 = y*w*2.0f;
	float yz2 = y*z*2.0f;
	float zw2 = z*w*2.0f;

	return eoeVec3(
		(xxzz + wwyy)*a.x + (xy2 - zw2)*a.y + (xz2 + yw2)*a.z,
		(xy2 + zw2)*a.x + (y*y + w*w - x*x - z*z)*a.y + (yz2 - xw2)*a.z,
		(xz2 - yw2)*a.x + (yz2 + xw2)*a.y + (wwyy - xxzz)*a.z 
	);
}

//-------------------------
// eoeQuat::operator*
// expanded and factored version of:
// (*this) * eoeQuat( a.x, a.y, 0.0f, 0.0f ) * (*this)^-1
// returns an eoeVec2 by rotating the given eoeVec2 
// counter-clockwise using *this eoeQuat.
// assumes a right-handed coordinate system
// --only deals with unit length quaternions--
//-------------------------
inline eoeVec2 eoeQuat::operator*(const eoeVec2 &a) const {
	float xxzz = x*x - z*z;
	float wwyy = w*w - y*y;

	float xy2 = x*y*2.0f;
	float zw2 = z*w*2.0f;

	return eoeVec2(
		(xxzz + wwyy)*a.x + (xy2 - zw2)*a.y,
		(xy2 + zw2)*a.x + (y*y + w*w - x*x - z*z)*a.y
	);
}

//-------------------------
// eoeQuat::Inverse
// returns an eoeQuat that is the inverse of *this
// unit length quaternion have inverse == conjugate
//-------------------------
inline eoeQuat eoeQuat::Inverse() const {
	return eoeQuat(-x, -y, -z, w);
}

//-------------------------
// eoeQuat::Set
// sets this x,y,z, and w to the given values
//-------------------------
inline void eoeQuat::Set(const float x, const float y, const float z, const float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

#endif /* EOECORE_VECTOR_H */

