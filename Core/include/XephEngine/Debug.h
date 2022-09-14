#pragma once
//#include "../Libraries.h"

namespace xe
{
	namespace Debug
	{
		//Window
		void Setup(bool DEBUG_MODE);
		void ShutDown();

		void Log(const char* fmt, ...);
		void LogWarn(const char* fmt, ...);
		void LogErr(const char* fmt, ...);
	}
}

