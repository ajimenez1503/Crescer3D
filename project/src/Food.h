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
			int getWeight();
		private:
			int m_weight;

		
	};
}

#endif // _FOOD_H
