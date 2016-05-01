#ifndef _Camera_H
#define _Camera_H

#include "System.h"
#include "Logger.h"

namespace Crescer3D
{
	class Camera : public System
	{
	public:
		Camera();
		virtual ~Camera();
		virtual bool Initialize();
	};
}

#endif // _Camera_H