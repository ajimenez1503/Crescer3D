#include "Player.h"

namespace Crescer3D
{
	Player::Player()
	: System(SystemType::Sys_Player)
	{
	}

	Player::~Player()
	{
	}

	bool Player::Initialize()
	{
		Logger::Log("Hello Player!");
		return true;
	}
}