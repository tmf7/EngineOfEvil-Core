#include "Input.h"

eoeInput eoeInput::input;

//----------------------
// eoeInput::~eoeInput
//----------------------
eoeInput::~eoeInput() {
	delete[] keys;
	delete[] prevKeys;
}

//----------------------
// eoeInput::Init
// DEBUG: succeeds or crashes the program
//----------------------
void eoeInput::Init() {
	const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	const Uint8 * keyboard = SDL_GetKeyboardState(&numKeys);

	oldMouseX = mouseX;
	oldMouseY = mouseY;

	try {
		keys = new Uint8[numKeys];
		prevKeys = new Uint8[numKeys];
	} catch (const std::bad_alloc & error) {
		EVIL_ERROR_LOG.ErrorPopupWindow("Input failed to initialize.");
		EVIL_ERROR_LOG.LogError(error.what(), __FILE__, __LINE__);
		throw;
	}

	memcpy(keys, keyboard, sizeof(keyboard[0]) * numKeys);
	memset(prevKeys, 0, sizeof(prevKeys[0]) * numKeys);

	for (int i = 1; i <= 3; i++) {
		prevMouseButtons[i - 1] = 0;
		mouseButtons[i - 1] = mouseState & SDL_BUTTON(i);
	}
}

//----------------------
// eoeInput::Update
// reads the current state of the keyboard and mouse and saves the previous state
//----------------------
void eoeInput::Update() {
	oldMouseX = mouseX;
	oldMouseY = mouseY;

	const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	const Uint8 * keyboard = SDL_GetKeyboardState(&numKeys);

	memcpy(prevKeys, keys, sizeof(prevKeys[0]) * numKeys);
	memcpy(keys, keyboard, sizeof(keys[0]) * numKeys);

	for (int i = 1; i <= 3; i++) {
		prevMouseButtons[i - 1] = mouseButtons[i - 1];
		mouseButtons[i - 1] = mouseState & SDL_BUTTON(i);
	}
}

//----------------------
// eoeInput::KeyHeld
// returns 1 if the key is currently being pressed, 0 if not, -1 if invalid key
//----------------------
int eoeInput::KeyHeld(int key) const {
	if (key < 0 || key > numKeys)
		return -1;

	return keys[key];
}

//----------------------
// eoeInput::KeyPressed
// returns 1 if the key changed state from released to pressed, 0 otherwise, -1 if invalid key
//----------------------
int eoeInput::KeyPressed(int key) const {
	if (key < 0 || key > numKeys)
		return -1;

	return (keys[key] & ~prevKeys[key]);
}

//----------------------
// eoeInput::KeyReleased
// returns 1 if the key changed state from pressed to released, 0 otherwise, -1 if invalid key
//----------------------
int eoeInput::KeyReleased(int key) const {
	if (key < 0 || key > numKeys)
		return -1;

	return (prevKeys[key] & ~keys[key]);
}

//----------------------
// eoeInput::MouseHeld
// returns 1 if the button is currently being pressed, 0 if not, -1 if invalid button
//----------------------
int eoeInput::MouseHeld(int button) const {
	if (button < SDL_BUTTON_LEFT || button > SDL_BUTTON_RIGHT)
		return -1;

	return mouseButtons[button - 1];
}

//----------------------
// eoeInput::MousePressed
// returns 1 if the button changed state from released to pressed, 0 if not, -1 if invalid button
//----------------------
int eoeInput::MousePressed(int button) const {
	if (button < SDL_BUTTON_LEFT || button > SDL_BUTTON_RIGHT)
		return -1;

	return (mouseButtons[button - 1] & ~prevMouseButtons[button - 1]);
}

//----------------------
// eoeInput::MouseReleased
// returns 1 if the button changed state from pressed to released, 0 if not, -1 if invalid button
//----------------------
int eoeInput::MouseReleased(int button) const {
	if (button < SDL_BUTTON_LEFT || button > SDL_BUTTON_RIGHT)
		return -1;

	return (prevMouseButtons[button - 1] & ~mouseButtons[button - 1]);
}

//----------------------
// eoeInput::MouseMoved
// returns true if the mouse x or y value has changed, false otherwise
//----------------------
bool eoeInput::MouseMoved() const {
	return (mouseX != oldMouseX || mouseY != oldMouseY);
}

//----------------------
// eoeInput::GetMouseX
// returns the current x-position of the mouse cursor within the focused window
//----------------------
int eoeInput::GetMouseX() const {
	return mouseX;
}

//----------------------
// eoeInput::GetMouseY
// returns the current y-position of the mouse cursor within the focused window
//----------------------
int eoeInput::GetMouseY() const {
	return mouseY;
}

//----------------------
// eoeInput::HideCursor
// returns the current y-position of the mouse cursor
//----------------------
void eoeInput::HideCursor(bool hide) const {
	if (hide)
		SDL_ShowCursor(SDL_DISABLE);
	else
		SDL_ShowCursor(SDL_ENABLE);
}


