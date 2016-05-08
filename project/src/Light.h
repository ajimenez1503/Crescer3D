#ifndef _LIGHT_H
#define _LIGHT_H

#include "../../common/VectorUtils3.h"

namespace Crescer3D
{
	class Light
	{
	public:
		Light();
		~Light();
		inline static vec3 GetLightPosition() { return vec3(0.0, 15.0, 0.0); };
		inline static vec3 GetLightDirection() { return vec3(0.1, 5.0, 0.0); };
	};
}

#endif // _LIGHT_H