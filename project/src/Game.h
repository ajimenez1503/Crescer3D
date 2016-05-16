#ifndef _GAME_H
#define _GAME_H


#include "System.h"
#include "Player.h"
#include "Enemy.h"
#include "Food.h"

#include "DeleteUtil.h"
#include "HighScore.h"
#include "Camera.h"
#include "Logger.h"
#include "Sound.h"

#include <list>
#include <time.h>

namespace Crescer3D
{	class Sound;

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
		static std::list<Enemy*> GetEnemyList();
		static void SetEnemyList(std::list<Enemy*> in_enemy_list);
		static std::list<Food*> GetFoodList();
		static void SetFoodList(std::list<Food*> in_food_list);	

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
		static std::list<Enemy*> m_enemy_list;		
		static std::list<Food*> m_food_list;
		static Camera* m_Camera;
		static GameStates gameState;
		static bool gameNeedReset;
	};
}

#endif // _GAME_H
