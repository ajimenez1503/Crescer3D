#ifndef _ENEMY_H
#define _ENEMY_H

#if defined (__LINUX__) || (__CENTOS__)
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __OSX__
	extern "C"
	{
		#include <OpenGL/gl3.h>
		#include "../../common/mac/MicroGlut.h"
	}
#endif

#if defined (__LINUX__) || (__CENTOS__)
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __OSX__
	extern "C"
	{
		#include <OpenGL/gl3.h>
		#include "../../common/mac/MicroGlut.h"
	}
#endif

#include "Logger.h"
#include "Sphere.h"
#include "Timing.h"
#include "Food.h"

namespace Crescer3D
{
	enum Goal_State
	{
		eat_player,
		eat_food,
		eat_enemy,
		explore,
		undefined
	};


	class Enemy : public Sphere
	{
		public:

			Enemy();
			virtual ~Enemy();
			virtual bool Initialize();

			Goal_State getGoalState();
			void setGoalState(Goal_State goal_state);

			int getWeight();
			void increaseWayWent();

			void eat(int weight_eaten);

			Food* getTargetFood();
			void setTargetFood(Food* target_food); 
			Enemy* getTargetEnemy();
			void setTargetEnemy(Enemy* target_enemy);

			float getMovementAngle();
			void setMovementAngle(float movement_angle);
	
		private:
			int m_weight;
			Goal_State m_goal_state;
			Food* m_target_food;
			Enemy* m_target_enemy;
			float m_movement_angle;
			

		
	};
}

#endif // _ENEMY_H
