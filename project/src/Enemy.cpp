#include "Enemy.h"



namespace Crescer3D
{

	Enemy::Enemy()
	{
		m_weight=5;
	}

	Enemy::~Enemy()
	{
	}

	bool Enemy::Initialize()
	{
		//Logger::Log("Hello Enemy!");
		return true;
	}

	int Enemy::getWeight()
	{
		return m_weight;
	}
}
