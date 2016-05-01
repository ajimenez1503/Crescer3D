#include "Camera.h"

namespace Crescer3D
{
	Camera::Camera()
	: System(SystemType::Sys_Camera)
	{
	}

	Camera::~Camera()
	{
	}

	bool Camera::Initialize()
	{
		Logger::Log("Hello Camera!");
		return true;
	}
}
