#ifndef _GAME_H
#define _GAME_H

#include "System.h"
#include <iostream>

namespace Crescer3D
{
	class Game : public System
	{
	public:
		Game();
		virtual ~Game();

		virtual bool Update();
	};
}

#endif // _GAME_H