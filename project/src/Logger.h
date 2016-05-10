#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <string>
#include "../../common/VectorUtils3.h"
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
		static void Log(vec3 v);

		template<class T>
		static void Log(const char* c, T v)
		{
			std::cout << c << v << std::endl;
		}
	};
}

#endif // _LOGGER_H