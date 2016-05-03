#include "Logger.h"

namespace Crescer3D
{
	Logger::Logger()
	: System(SystemType::Sys_Logger)
	{
	}

	Logger::~Logger()
	{
	}

	void Logger::Log(const char* c)
	{
		std::cout << c << std::endl;
	}

	void Logger::Log(char* c)
	{
		std::cout << c << std::endl;
	}

	void Logger::Log(std::string s)
	{
		std::cout << s << std::endl;
	}

	void Logger::Log(float f)
	{
		std::cout << f << std::endl;
	}

	void Logger::Log(vec3 v)
	{
		std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
	}
}