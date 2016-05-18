#include "Enemy.h"

namespace Crescer3D
{

	Enemy::Enemy()
	{
		this->setWeight(5);
		this->setRadius(log(this->getWeight()));
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
		this->setWayWent(0.0);
		m_goal_state=goal_state;
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
	void Enemy::setTargetEnemy(Enemy* target_enemy)
	{
		m_target_enemy=target_enemy;
	}

	float Enemy::getMovementAngle()
	{
		return m_movement_angle;
	}
	void Enemy::setMovementAngle(float movement_angle)
	{
		m_movement_angle=movement_angle;
	}

}
