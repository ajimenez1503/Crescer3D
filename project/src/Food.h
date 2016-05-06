#ifndef _FOOD_H
#define _FOOD_H

#include "Logger.h"
#include "Cube.h"

namespace Crescer3D
{
	class Food : public Cube
	{
		public:
			Food();
			virtual ~Food();
			virtual bool Initialize();

		
	};
}

#endif // _FOOD_H
