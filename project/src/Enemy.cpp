#include "Enemy.h"

namespace Crescer3D
{
	Enemy::Enemy()
	{
		m_weight=5;
		m_goal_state=undefined;
	}

	Enemy::~Enemy()
	{
	}

	bool Enemy::Initialize()
	{
		//Logger::Log("Hello Enemy!");
		return true;
	}

	Goal_State Enemy::getGoalState()
	{
		return m_goal_state;
	}

	void Enemy::setGoalState(Goal_State goal_state)
	{
		if(goal_state!=undefined)
		{
			unsigned long gameisRunning = Timing::GetGameSeconds();
			// Save the seconds when you set a state and check
			// after some time if more then X seconds are gone.
		}
		else
		{
			std::cout<<"Reset enemy State"<<std::endl;
		}
		
		m_goal_state=goal_state;
	}

	void Enemy::Timer(int i)
	{
		setGoalState(undefined);
	}
	
	int Enemy::getWeight()
	{
		return m_weight;
	}
}
