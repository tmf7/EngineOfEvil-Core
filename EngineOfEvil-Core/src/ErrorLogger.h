#ifndef EOECORE_ERROR_LOGGER
#define EOECORE_ERROR_LOGGER

#include <string>
#include <fstream>
#include <SDL.h>

//------------------------------------------
//			eoeErrorLogger
// "singleton" class for output to error log file
// in project directory and displaying runtime
// popup error messages
//-------------------------------------------
class eoeErrorLogger {
public:
				
									eoeErrorLogger();							
								   ~eoeErrorLogger();

	void							ErrorPopupWindow(const char * message);
	void							LogError(const char * message, const char * sourceFilepath, int lineOfCode);
	void							CheckSDLError(const char * sourceFilepath, int lineOfCode);

private:

	std::ofstream					logStream;
	std::string						logFilepath;
};

extern eoeErrorLogger errorLog;

//--------------------
// VerifyWrite (global)
// closes the stream if it's corrupted
//--------------------
inline bool VerifyWrite(std::ofstream & write) {
	if (write.bad() || write.fail()) {
		write.close();
		return false;
	}
	return true;
}

//--------------------
// VerifyRead (global)
// clears and closes the stream if it's corrupted
//--------------------
inline bool VerifyRead(std::ifstream & read) {
	if (read.bad() || read.fail()) {
		read.clear();
		read.close();
		return false;
	}
	return true;
}

#endif /* EOECORE_ERROR_LOGGER */