#include "Player.h"



namespace Crescer3D
{
	
	Player::Player()
	{
		this->setWeight(5);
		this->setRadius(log(this->getWeight()));
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



	
	
}
