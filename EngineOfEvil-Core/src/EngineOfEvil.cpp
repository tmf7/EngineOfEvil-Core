#include "EngineOfEvil.h"

//---------------------------
// InitEngineOfEvil (global)
// initializes all engine-critical systems in-order
// returns false on failure, true on success
//---------------------------
bool InitEngineOfEvil() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // SDL Failed to Initialize.
		return false;

	if (!EVIL_ERROR_LOG.Init())
		return false;

	EVIL_INPUT.Init();						// succeeds or crashes, but still logs the error

	return true;
}

//---------------------------
// ShutdownEngineOfEvil (global)
// TODO: shutdown/destroy any systems that need shutting down in-order
//---------------------------
void ShutdownEngineOfEvil() {
//	EVIL_INPUT;
//	EVIL_ERROR_LOG;
}

//---------------------------
// UpdateEngineOfEvil (global)
// TODO: update all systems that need updating in-order
//---------------------------
void UpdateEngineOfEvil() {
	EVIL_INPUT.Update();
}