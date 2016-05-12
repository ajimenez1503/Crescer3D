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
			glutTimerFunc(3, &Crescer3D::Enemy::Timer,0);
		}else
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
