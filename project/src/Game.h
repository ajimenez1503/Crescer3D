#ifndef _GAME_H
#define _GAME_H

#include "System.h"
#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include "Sphere.h"
#include "Cube.h"
#include "DeleteUtil.h"
#include "HighScore.h"
#include "Camera.h"

//#include <list>

namespace Crescer3D
{	
	class Camera;
	enum GameStates
	{
		Game_Init,
		Game_Play,
		Game_GameOver,
	};
	class Game : public System
	{
	public:
		Game();
		virtual ~Game();
		virtual bool Update();
		virtual bool Initialize();
		virtual bool ShutDown();

		static Player* GetPlayer();
		static Enemy* GetEnemy();
		static Cube* GetFood();
		static Camera* GetCamera();


		static void GameOver();
		static void SetGameStateInit();
		static void SetGameStatePlay();
		static void SetGameStateGameOver();
		static bool IsStateInit();
		static bool IsStatePlay();
		static bool IsStateGameOver();
		static void ResetGame();

	private:
		static Player* m_Player;
		//static std::list<Enemy> enemy_list;
		static Enemy* m_Enemy;
		static Cube * m_Food;
		//static std::list<Food> food_list;
		static Camera* m_Camera;
		static GameStates gameState;
		static bool gameNeedReset;
	};
}

#endif // _GAME_H
