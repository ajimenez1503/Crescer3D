#include "System.h"

namespace Crescer3D
{
	SystemData::SystemData(const SystemType& type)
	: systemType(type)
	{}

	System::System(const SystemData& data)
	: m_SystemType(data.systemType)
	{}

	System::~System()
	{}
}
