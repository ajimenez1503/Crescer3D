#ifndef _ENGINE_H
#define _ENGINE_H

#include "Platform.h"

#ifdef __LINUX__
	extern "C"
	{
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
#include "Game.h"
#include "Input.h"
#include "DeleteUtil.h"

namespace Crescer3D
{
	// Forward Declaration
	class System;
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
		Engine();
		~Engine();
		bool runMainLoop();
		static EngineState GetEngineState() { return m_EngineState; }

	private:
		static EngineState m_EngineState;
		std::map<Crescer3D::SystemType, Crescer3D::System*> m_mapSystems;

		int Initialize();
		int Update();
		int Shutdown();

		Crescer3D::Game* CreateGame();

		int AddSystem(Crescer3D::System* pSys);

		// Retrieve a core system from the engine
		template<typename T>
		T* GetSystem(Crescer3D::SystemType sysType)
		{
			T* psys = static_cast<T*>(m_mapSystems[sysType]);
			if (!psys)
			{
				// Logger::Log("System is not valid");
				return nullptr;
			}
			return psys;
		}
	};
}

#endif // _ENGINE_H