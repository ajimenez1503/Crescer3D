#include "Sound.h"

namespace Crescer3D
{
#ifndef __CENTOS__
	irrklang::ISoundEngine* Sound::engine;
	irrklang::ISoundSource* background;
	irrklang::ISoundSource* eatFood;
	irrklang::ISoundSource* eatEnemy;
	irrklang::ISoundSource* gameOver;


#endif

	Sound::Sound()
	: System(SystemType::Sys_Sound)
	{

	}

	Sound::~Sound()
	{
#ifndef __CENTOS__
		if(engine)
			engine->drop(); // delete sound engine
#endif
	}

	bool Sound::Initialize()
	{
#ifndef __CENTOS__
		engine = irrklang::createIrrKlangDevice();

		if(!engine) {
			Logger::Log("Could not startup engine\n");
			return false;
		}
		else
			this->playBackgroundMusic();
#endif
			return true;
	}

	void Sound::playBackgroundMusic()
	{
#ifndef __CENTOS__
		if(engine)
		{
			engine->play2D("sounds/backgroundMusic.mp3",true);
		}
#endif
	}

	void Sound::playEatFoodMusic()
	{
#ifndef __CENTOS__
		if(engine)
		{
			engine->play2D("sounds/eatFood.wav");
		}
#endif
	}

	void Sound::playEatEnemyMusic()
	{
#ifndef __CENTOS__
		if(engine)
		{
			engine->play2D("sounds/eatEnemy.wav");
		}
#endif
	}

	void Sound::playGameOverMusic()
	{
#ifndef __CENTOS__
		if(engine)
		{
			engine->play2D("sounds/gameOver.mp3");
		}
#endif
	}
} 