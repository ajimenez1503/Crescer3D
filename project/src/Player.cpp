#include "Player.h"



namespace Crescer3D
{
	// forward declaration of static members
	int Player::m_weight;

	Player::Player()
	{
		m_weight=5;
		this->setRadius(m_weight/5.0);
		this->setVelocity(0.2f);
	}

	Player::~Player()
	{
	}

	bool Player::Initialize()
	{
		//Logger::Log("Hello Player!");
		return true;
	}

	int Player::getWeight()
	{
		return m_weight;
	}

	void Player::eat(int weight_eaten)
	{
		m_weight=m_weight+weight_eaten;
		//std::cout<< "m_weight:"<<m_weight<<std::endl;
		//float radius=this->getRadius();
		this->setRadius(m_weight/5.0);	
	}

	
	
}
