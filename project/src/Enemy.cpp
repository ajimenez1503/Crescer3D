#include "Enemy.h"



namespace Crescer3D
{
	Enemy::Enemy()
	: System(SystemType::Sys_Enemy)
	{
	}

	Enemy::~Enemy()
	{
	}

	bool Enemy::Initialize()
	{
		//Logger::Log("Hello Enemy!");
		return true;
	}
}
