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
		inline static vec3 GetLightDirection() { return vec3(10.0, 5.0, 0); };
	};
}

#endif // _LIGHT_H