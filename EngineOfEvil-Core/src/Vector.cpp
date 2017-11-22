#include "Vector.h"

eoeVec2 vec2_zero		( 0.0f, 0.0f );
eoeVec2 vec2_oneZero	( 1.0f, 0.0f );
eoeVec2 vec2_zeroOne	( 0.0f, 1.0f );
eoeVec2 vec2_one		( 1.0f, 1.0f );
eoeVec2 vec2_epsilon	(FLT_EPSILON, FLT_EPSILON);

eoeVec3 vec3_right		( 1.0f,  0.0f,  0.0f );
eoeVec3 vec3_left		(-1.0f,  0.0f,  0.0f );
eoeVec3 vec3_up			( 0.0f, -1.0f,  0.0f );
eoeVec3 vec3_down		( 0.0f,  1.0f,  0.0f );
eoeVec3 vec3_forward	( 0.0f,  0.0f,  1.0f );
eoeVec3 vec3_back		( 0.0f,  0.0f, -1.0f );
eoeVec3 vec3_zero		( 0.0f,  0.0f,  0.0f );
eoeVec3 vec3_one		( 1.0f,  1.0f,  1.0f );

eoeVec3	eoeQuat::Rotate(const eoeVec3 & rotationAxis, float degrees, const eoeVec3 & toRotate) {
	const eoeVec3 quatXYZ = rotationAxis * SDL_sinf(eoeMath::ToRadians(degrees) * 0.5f);
	const eoeQuat rotation( quatXYZ.x, quatXYZ.y, quatXYZ.z, SDL_cosf(eoeMath::ToRadians(degrees) * 0.5f));
	return rotation * toRotate;
}


eoeVec2	eoeQuat::Rotate(const eoeVec3 & rotationAxis, float degrees, const eoeVec2 & toRotate) {
	const eoeVec3 quatXYZ = rotationAxis * SDL_sinf(eoeMath::ToRadians(degrees) * 0.5f);
	const eoeQuat rotation( quatXYZ.x, quatXYZ.y, quatXYZ.z, SDL_cosf(eoeMath::ToRadians(degrees) * 0.5f));
	return rotation * toRotate;
}

void eoeQuat::Rotate(const eoeVec3 & rotationAxis, float degrees, eoeVec3 & toRotate) {
	const eoeVec3 quatXYZ = rotationAxis * SDL_sinf(eoeMath::ToRadians(degrees) * 0.5f);
	const eoeQuat rotation( quatXYZ.x, quatXYZ.y, quatXYZ.z, SDL_cosf(eoeMath::ToRadians(degrees) * 0.5f));
	toRotate = rotation * toRotate;
}

void eoeQuat::Rotate(const eoeVec3 & rotationAxis, float degrees, eoeVec2 & toRotate) {
	const eoeVec3 quatXYZ = rotationAxis * SDL_sinf(eoeMath::ToRadians(degrees) * 0.5f);
	const eoeQuat rotation( quatXYZ.x, quatXYZ.y, quatXYZ.z, SDL_cosf(eoeMath::ToRadians(degrees) * 0.5f));
	toRotate = rotation * toRotate;
}