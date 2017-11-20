#include "ErrorLogger.h"

eoeErrorLogger errorLog;

//-------------------
// eoeErrorLogger::eoeErrorLogger
//------------------
eoeErrorLogger::eoeErrorLogger()
	: logFilepath("../Logs/EngineOfEvilCore(") {
	logFilepath += __DATE__;
	logFilepath += ").log";
	logStream.open(logFilepath, std::ios::out | std::ios::app);

	if (!VerifyWrite(logStream))
		ErrorPopupWindow("Failed to initialize error output log.");

	LogError("------------------------------STARTING RUN------------------------------", __FILE__, __LINE__);
}

//-------------------
// eoeErrorLogger::~eoeErrorLogger
//------------------
eoeErrorLogger::~eoeErrorLogger() {
	if (logStream.is_open()) {
		LogError("------------------------------ENDING RUN------------------------------", __FILE__, __LINE__);
		logStream.close();
	}
}

//--------------------
// eoeErrorLogger::ErrorPopupWindow
// immediatly shows a small dialog box with the intended message
// does not log the error, be sure to call LogError as needed
//--------------------
void eoeErrorLogger::ErrorPopupWindow(const char * message) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", message, NULL);
}

//--------------------
// eoeErrorLogger::LogError
// outputs error message to the log file in project directory
//--------------------
void eoeErrorLogger::LogError(const char * message, const char * sourceFilepath, int lineOfCode) {
	if (!VerifyWrite(logStream)) {
		ErrorPopupWindow("Log output stream corrupted. Log closed.");
		return;
	}

	logStream << "\n\n" << message;
	logStream << "\nFile: " << sourceFilepath << "\nLine: " << lineOfCode;
}


//--------------------
// eoeErrorLogger::LogSDLError
// checks the status of any SDL errors and logs them
//--------------------
void eoeErrorLogger::CheckSDLError(const char * sourceFilepath, int lineOfCode) {
	const std::string error(SDL_GetError());

	if (error != "") {
		const std::string message("\nSDL Error : ");
		LogError((message + error).c_str(), sourceFilepath, lineOfCode);
		SDL_ClearError();
	}
}
