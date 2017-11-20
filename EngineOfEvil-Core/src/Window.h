#ifndef EOECORE_WINDOW_H
#define EOECORE_WINDOW_H

#include <string>
#include <glew.h>
#include <SDL.h>
#include "ErrorLogger.h"

//--------------------------------------------
//			eoeWindow
// wrapper class for a single window
// and its associated opengl rendering context,
// polls events that occur within is area
//--------------------------------------------
class eoeWindow {
public:

							eoeWindow(Uint32 width, Uint32 height, const char * title);
						   ~eoeWindow();

	bool					IsOpen() const;
	void					Clear() const;
	void					Resize(Uint32 newWidth, Uint32 newHeight);
	void					Update();

private:

	bool					Init();
	void					PollEvents();

private:

	SDL_Window *			window;
	SDL_GLContext			context;
	std::string				title;
	Uint32					width;
	Uint32					height;
	bool					isOpen;
};

#endif /* EOECORE_WINDOW_H */