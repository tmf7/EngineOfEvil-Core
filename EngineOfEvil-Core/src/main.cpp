#include "Window.h"

int main(int argc, char* argv[]) {

	eoeWindow window(800, 600, "Engine Of Evil Core");

	glClearColor(0.5f, 0.2f, 0.8f, 1.0f);

	while (window.IsOpen()) {
		window.Clear();
		window.Update();
	}

	return 0;
}