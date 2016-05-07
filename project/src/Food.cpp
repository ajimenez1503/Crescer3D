#include "Food.h"



namespace Crescer3D
{
	Food::Food()
	{
		m_weight=1;
	}

	Food::~Food()
	{
	}

	bool Food::Initialize()
	{
		//Logger::Log("Hello Food!");
		return true;
	}

	int Food::getWeight()
	{
		return m_weight;
	}
}
