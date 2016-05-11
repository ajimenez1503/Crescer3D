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
			//std::cout<<"Reset enemy State"<<std::endl;
		}
		
		m_goal_state=goal_state;
	}

	
	int Enemy::getWeight()
	{
		return m_weight;
	}

	void Enemy::eat(int weight_eaten)
	{
		m_weight=m_weight+weight_eaten;
		//std::cout<< "m_weight:"<<m_weight<<std::endl;
		//float radius=this->getRadius();
		this->setRadius(m_weight/5.0);	
	}

	Food* Enemy::getTargetFood()
	{
		return m_target_food;
	}
	void Enemy::setTargetFood(Food* target_food)
	{
		m_target_food=target_food;
	} 
	Enemy* Enemy::getTargetEnemy()
	{
		return m_target_enemy;
	}
	void Enemy::setEnemyFood(Enemy* target_enemy)
	{
		m_target_enemy=target_enemy;
	}

}
