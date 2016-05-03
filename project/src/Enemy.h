#ifndef _ENEMY_H
#define _ENEMY_H

#include "System.h"
#include "Logger.h"
#include "Sphere.h"

namespace Crescer3D
{
	class Enemy : public System, public Sphere
	{
		public:
			Enemy();
			virtual ~Enemy();
			virtual bool Initialize();

		
	};
}

#endif // _ENEMY_H
