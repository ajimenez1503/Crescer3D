#include "Game.h"

namespace Crescer3D
{
		Game::Game()
			: System(SystemType::Sys_Game)
		{
		}

		Game::~Game()
		{
		}

		bool Game::Update()
		{
			//std::cout << "Game is Running!" << std::endl;
			return true;
		}
}