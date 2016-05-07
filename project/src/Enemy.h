#ifndef _ENEMY_H
#define _ENEMY_H

#include "Logger.h"
#include "Sphere.h"

namespace Crescer3D
{
	class Enemy : public Sphere
	{
		public:

			Enemy();
			virtual ~Enemy();
			virtual bool Initialize();
			int getWeight();
	
		private:
			int m_weight;

		
	};
}

#endif // _ENEMY_H
