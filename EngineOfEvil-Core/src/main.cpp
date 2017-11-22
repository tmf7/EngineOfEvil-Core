#include "Window.h"
#include "EngineOfEvil.h"
#include <iostream>

#include "Matrix.h"

int main(int argc, char* argv[]) {

	if (!InitEngineOfEvil())
		return -1;

	eoeMat4 a = eoeMat4::GetTranslation(eoeVec3(1.0f, 2.0f, 3.0f));
	eoeVec4 v1;		// all zeroes
	eoeVec4 v2;
	v2.w = 1.0f;

	auto tV1 = a * v1;
	auto tV2 = a * v2;

	std::cout << "v1: " << v1.x  << ", " <<v1.y	<< ", " << v1.z << std::endl;
	std::cout << "tV1: " << tV1.x << ", " << tV1.y << ", " << tV1.z << std::endl;
	std::cout << "v2: " << v2.x  << ", " << v2.y	<< ", " << v2.z << std::endl;
	std::cout << "tV2: " << tV2.x << ", " << tV2.y << ", " << tV2.z << std::endl;

	a *= mat4_identity;

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			std::cout << a[r][c] << '\t';
			if (c == 3)
				std::cout << '\n';
		}
	}


	eoeWindow window(800, 600, "Engine Of Evil Core");

	glClearColor(0.5f, 0.2f, 0.8f, 1.0f);

	while (window.IsOpen()) {
		window.Clear();
		UpdateEngineOfEvil();
		if (EVIL_INPUT.KeyPressed(SDL_SCANCODE_SPACE))
			std::cout << "PRESSED\n";
		window.Update();
	}

	return 0;
}