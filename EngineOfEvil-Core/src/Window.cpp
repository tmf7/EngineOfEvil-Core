#include "Window.h"

//------------------------
// eoeWindow::eoeWindow
// creates the main window for the engine
//------------------------
eoeWindow::eoeWindow(Uint32 width, Uint32 height, const char* title)
	: width(width), height(height), title(title) {
	if(!Init())
		this->~eoeWindow();
}

//------------------------
// eoeWindow::~eoeWindow
//------------------------
eoeWindow::~eoeWindow() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//------------------------
// eoeWindow::Init
// sets up the window, creates a current opengl context for it, and initializes glew
//------------------------
bool eoeWindow::Init() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);		// newer openGl functionality only
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(	title.c_str(), 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								width, 
								height, 
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::string message("Window failed to initialize: ");
		message += title;
		EVIL_ERROR_LOG.ErrorPopupWindow(message.c_str());
		return false;
	}

	context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		EVIL_ERROR_LOG.ErrorPopupWindow("OpenGL context creation failed.");
		return false;
	}
	SDL_GL_SetSwapInterval(1);					// vsync, if available


	#ifndef __APPLE__
	glewExperimental = GL_TRUE;					// allow latest driver extensions
	if(glewInit() != GLEW_OK) {
		EVIL_ERROR_LOG.ErrorPopupWindow("GLEW failed to initialize.");
		return false;
	}
	#endif

	isOpen = true;
	return true;
}

//------------------------
// eoeWindow::IsOpen
//------------------------
bool eoeWindow::IsOpen() const {
	if (!isOpen)
		this->~eoeWindow();
	return isOpen;
}

//------------------------
// eoeWindow::Clear
//------------------------
void eoeWindow::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//------------------------
// eoeWindow::Resize
//------------------------
void eoeWindow::Resize(Uint32 newWidth, Uint32 newHeight) {
	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height);
}

//------------------------
// eoeWindow::PollEvents
//------------------------
void eoeWindow::PollEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
				isOpen = false;
				break;
			}
			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					Resize((Uint32)event.window.data1, (Uint32)event.window.data2);
					break;
				}
			}
		}
	}
}

//------------------------
// eoeWindow::Update
// polls window events and swaps the buffers
//------------------------
void eoeWindow::Update() {
	PollEvents();
	SDL_GL_SwapWindow(window);
}