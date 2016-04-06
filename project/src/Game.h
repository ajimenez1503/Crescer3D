#ifndef _GAME_H
#define _GAME_H

#include "System.h"
#include "Sphere.h"
#include "DeleteUtil.h"

namespace Crescer3D
{
	class Game : public System
	{
	public:
		Game();
		virtual ~Game();
		virtual bool Update();
		static Sphere* GetPlayer();
		static Sphere* GetEnemy();

	private:
		static Sphere* m_Player;
		static Sphere* m_Enemy;
	};
}

#endif // _GAME_H