#include "EngineOfEvil.h"

//---------------------------
// InitEngineOfEvil (global)
// initializes all engine-critical systems in-order
// returns false on failure, true on success
//---------------------------
bool InitEngineOfEvil() {
	bool success = EVIL_ERROR_LOG.Init();
	EVIL_INPUT.Init();
	return success;
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