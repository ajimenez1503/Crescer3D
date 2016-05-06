#include "Food.h"



namespace Crescer3D
{
	Food::Food()
	: System(SystemType::Sys_Food)	
	{
	}

	Food::~Food()
	{
	}

	bool Food::Initialize()
	{
		//Logger::Log("Hello Food!");
		return true;
	}
}
