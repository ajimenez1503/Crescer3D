#include "Sound.h"

namespace Crescer3D
{
	irrklang::ISoundEngine* Sound::engine;

	Sound::Sound()
	: System(SystemType::Sys_Sound)
	{
	}

	Sound::~Sound()
	{
		engine->drop(); // delete sound engine
	}

	bool Sound::Initialize()
	{
		return true;
	}

	void Sound::playSound(int index)
	{
		engine = irrklang::createIrrKlangDevice(); //create sound engine

		if (!engine)
		{			
			Logger::Log("Could not startup engine\n");
		}

		// play sounds accourding to index 
		if (index == 1)
		{
			engine->play2D("sounds/slurp.wav");
		}
		if (index == 2)
		{
			engine->play2D("sounds/male-thijs-loud-scream.wav");
		}
	}
} 