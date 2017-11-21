#ifndef EOECORE_INPUT_H
#define EOECORE_INPUT_H

#include <memory>
#include <SDL.h>
#include "ErrorLogger.h"

#define EVIL_INPUT (eoeInput::input)

//------------------------------------------------
//				eoeoeInput
// singleton that handles user input from mouse and keyboard
// on the device that's running this program
//------------------------------------------------
class eoeInput {
public:

	void					Init();
	void					Update();
	int						KeyHeld(int key) const;
	int						KeyPressed(int key) const;
	int						KeyReleased(int key) const;
	int						MouseHeld(int button) const;
	int						MousePressed(int button) const;
	int						MouseReleased(int button) const;
	bool					MouseMoved() const;
	int						GetMouseX() const;
	int						GetMouseY() const;
	void					HideCursor(bool hide = true) const;

private:

							eoeInput() = default;
						   ~eoeInput();

							eoeInput(const eoeInput & other) = delete;
							eoeInput(eoeInput && other) = delete;

	eoeInput &				operator=(const eoeInput & other) = delete;
	eoeInput				operator=(eoeInput && other) = delete;

public:

	static eoeInput			input;

private:

	Uint8 *					keys		= nullptr;
	Uint8 *					prevKeys	= nullptr;
	int						numKeys		= 0;

	int						mouseButtons[3];
	int						prevMouseButtons[3];
	int						mouseX;
	int						mouseY;
	int						oldMouseX;
	int						oldMouseY;
};

#endif /* EOECORE_INPUT_H */

