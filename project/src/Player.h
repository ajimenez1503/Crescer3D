#ifndef _PLAYER_H
#define _PLAYER_H

#include "System.h"
#include "Logger.h"

namespace Crescer3D
{
	class Player : public System
	{
	public:
		Player();
		virtual ~Player();
		virtual bool Initialize();
	};
}

#endif // _PLAYER_H