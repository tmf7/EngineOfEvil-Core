#ifndef EOECORE_ENGINE_STARTUP_H
#define EOECORE_ENGINE_STARTUP_H

#include "Input.h"

//---------------------------
// InitEngineOfEvil (global)
// initializes all engine-critical systems in-order
// returns false on failure, true on success
//---------------------------
bool InitEngineOfEvil();

//---------------------------
// ShutdownEngineOfEvil (global)
// TODO: shutdown/destroy any systems that need shutting down in-order
//---------------------------
void ShutdownEngineOfEvil();

//---------------------------
// UpdateEngineOfEvil (global)
// TODO: update all systems that need updating in-order
//---------------------------
void UpdateEngineOfEvil();

#endif /* EOECORE_ENGINE_STARTUP_H */