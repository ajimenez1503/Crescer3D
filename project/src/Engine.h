#ifndef _ENGINE_H
#define _ENGINE_H

#if defined (__LINUX__) || (__CENTOS__)
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __OSX__
	extern "C"
	{
		#include <OpenGL/gl3.h>
		#include "../../common/mac/MicroGlut.h"
	}
#endif
#include <map>
#include "System.h"
#include "Window.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Game.h"
#include "Input.h"
#include "Logger.h"
#include "HighScore.h"
#include "GUI.h"
#include "DeleteUtil.h"
#include "Sound.h"
#include "Timing.h"

namespace Crescer3D
{

	// Forward Declarations in main file
	class System;
	class Window;
	class Player;
	class Camera;
	class Enemy;
	class Game;
	class Input;
	class Logger;
	class HighScore;
	class GUI;
	class Sound;

	enum  SystemType;

	enum EngineState
	{
		Invalid,
		Constructing,
		Initializing,
		Running,
		ShuttingDown,
		Destroying
	};

	class Engine
	{

	public:
		~Engine();

		bool runMainLoop();
		int Shutdown();

		static EngineState GetEngineState() { return m_EngineState; }
		static void SetEngineState(EngineState);
		static Engine* GetEngine();
		unsigned long GetWorldSeconds();
		unsigned long GetGameSeconds();

	private:
		Engine();

		static Engine* m_Engine;
		static EngineState m_EngineState;
		std::map<Crescer3D::SystemType, Crescer3D::System*> m_mapSystems;
		int Initialize();
		int Update();

		Crescer3D::Game* CreateGame();

		int AddSystem(Crescer3D::System* pSys);

		// Retrieve a core system from the engine
		template<typename T>
		T* GetSystem(Crescer3D::SystemType sysType)
		{
			T* psys = static_cast<T*>(m_mapSystems[sysType]);
			if (!psys)
			{
				Logger::Log("System is not valid");
				return NULL;
			}
			return psys;
		}
	};
}

#endif // _ENGINE_H
