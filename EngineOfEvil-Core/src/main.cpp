#include "Window.h"
#include "EngineOfEvil.h"
#include <iostream>

int main(int argc, char* argv[]) {

	if (!InitEngineOfEvil())
		return -1;

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