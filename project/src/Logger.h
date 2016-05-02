#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <string>
#include "System.h"

namespace Crescer3D
{
	class Logger : public System
	{
	public:
		Logger();
		virtual ~Logger();
		static void Log(const char* c);
		static void Log(std::string s);
		static void Log(char* c);
		static void Log(float f);
	};
}

#endif // _LOGGER_H