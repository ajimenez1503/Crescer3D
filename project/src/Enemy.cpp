#include "Enemy.h"

namespace Crescer3D
{

	Enemy::Enemy()
	{
		m_weight=5;
		m_goal_state=undefined;
		this->setRadius(m_weight/5.0);
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

	
	int Enemy::getWeight()
	{
		return m_weight;
	}

	void Enemy::eat(int weight_eaten)
	{
		m_weight=m_weight+weight_eaten;
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
