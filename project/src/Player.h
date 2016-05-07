#ifndef _PLAYER_H
#define _PLAYER_H

#include "Logger.h"
#include "Sphere.h"
#include "Food.h"
#

namespace Crescer3D
{
	class Player : public Sphere
	{
		public:
			Player();
			virtual ~Player();
			virtual bool Initialize();
			void eat(int weight_eaten);
			int getWeight();
		private:
			static int m_weight;
			

		
	};
}

#endif // _PLAYER_H
