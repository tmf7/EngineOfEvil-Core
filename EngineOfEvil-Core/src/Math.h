#ifndef EOECORE_MATH_H
#define EOECORE_MATH_H

#include <math.h>

//----------------------------------
//			eoeMath
//	  general math utilities
//----------------------------------
class eoeMath {
public:

	static float					NearestFloat(float x);
	static int						NearestInt(float x);
	static void						IsometricToOrthographic(float & x, float & y);
	static void						IsometricToOrthographic(int & x, int & y);
	static void						OrthographicToIsometric(float & x, float & y);
	static void						OrthographicToIsometric(int & x, int & y);
	static float					GetAngle(float x, float y);
	static float					RadiansToDegrees(float radians);
	static float					DegreesToRadians(float degrees);

public:
	
	static const constexpr float	RAD2DEG_CFACTOR = 180.0f / (float)M_PI;
	static const constexpr float	DEG2RAD_CFACTOR = (float)M_PI / 180.0f;
};

//--------------------
// eoeMath::NearestFloat
//--------------------
inline float eoeMath::NearestFloat(float x) {
	return floorf(x + 0.5f);
}

//--------------------
// eoeMath::NearestInt
//--------------------
inline int eoeMath::NearestInt(float x) {
	return (int)(x + 0.5f);
}

//--------------------
// eoeMath::IsometricToOrthographic
// rotates input coordinates ~45 degrees counter-clockwise
//--------------------
inline void eoeMath::IsometricToOrthographic(float & x, float & y) {
	float isoX = x;
	float isoY = y;
	x = (2.0f * isoY + isoX) * 0.5f;
	y = (2.0f * isoY - isoX) * 0.5f;
}

//--------------------
// eoeMath::IsometricToOrthographic
// rotates input coordinates ~45 degrees counter-clockwise
//--------------------
inline void eoeMath::IsometricToOrthographic(int & x, int & y) {
	float isoX = (float)x;
	float isoY = (float)y;
	x = NearestInt((2.0f * isoY + isoX) * 0.5f);
	y = NearestInt((2.0f * isoY - isoX) * 0.5f);
}

//--------------------
// eoeMath::OrthographicToIsometric
// rotates input coordinates ~45 degrees clockwise
//--------------------
inline void eoeMath::OrthographicToIsometric(float & x, float & y) {
	float cartX = x;
	float cartY = y;
	x = cartX - cartY;
	y = (cartX + cartY) * 0.5f;
}

//--------------------
// eoeMath::OrthographicToIsometric
// rotates input coordinates ~45 degrees clockwise 
//--------------------
inline void eoeMath::OrthographicToIsometric(int & x, int & y) {
	int cartX = x;
	int cartY = y;
	x = cartX - cartY;
	y = NearestInt((float)(cartX + cartY) * 0.5f);
}

//--------------------
// eoeMath::GetAngle
// returns the angle in degrees from the given components
// DEBUG: assumes components are part of a normalized vector
//--------------------
inline float eoeMath::GetAngle(float x, float y) {
	float angle = 0.0f;
	if (x == 0.0f && y > 0.0f) {
		return 90.0f;
	} else if (x == 0.0f && y < 0.0f) {
		return 270.0f;
	} else {
		float tan = y / x;
		angle = RadiansToDegrees(atanf(tan));
		if (x < 0)
			angle += 180.0f;
	}
	return angle;
}

//--------------------
// eoeMath::RadiansToDegrees
//--------------------
inline float eoeMath::RadiansToDegrees(float radians) {
	return (radians * RAD2DEG_CFACTOR);
}

//--------------------
// eoeMath::DegreesToRadians
//--------------------
inline float eoeMath::DegreesToRadians(float degrees) {
	return (degrees * DEG2RAD_CFACTOR);
}

#endif /* EOECORE_MATH_H */

