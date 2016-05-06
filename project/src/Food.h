#ifndef _FOOD_H
#define _FOOD_H

#include "System.h"
#include "Logger.h"
#include "Cube.h"

namespace Crescer3D
{
	class Food : public System, public Cube
	{
		public:
			Food();
			virtual ~Food();
			virtual bool Initialize();

		
	};
}

#endif // _FOOD_H
