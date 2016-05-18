#include "Player.h"



namespace Crescer3D
{
	// forward declaration of static members
	int Player::m_weight;

	Player::Player()
	{
		m_weight=5;
		this->setRadius(log(m_weight));
		//this->setVelocity(0.7f);
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
		this->setRadius(log(m_weight));	
	}

	
	
}
