#ifndef _GAME_H
#define _GAME_H


#include "System.h"
#include "Sphere.h"
#include "Cube.h"
#include "DeleteUtil.h"
#include "HighScore.h"
#include "Camera.h"



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
		static Sphere* GetPlayer();
		static Sphere* GetEnemy();
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
		static Sphere* m_Player;
		static Sphere* m_Enemy;
		static Cube * m_Food;
		static Camera* m_Camera;
		static GameStates gameState;
		static bool gameNeedReset;
	};
}

#endif // _GAME_H
