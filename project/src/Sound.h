#ifndef _Sound_H
#define _Sound_H

#include "System.h"
#include "Logger.h"

#ifndef __CENTOS__
	#include "../../irrKlang/include/irrKlang.h"
	#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#endif

namespace Crescer3D
{
	class Sound : public System
	{
	public:
		Sound();
		virtual ~Sound();
		virtual bool Initialize();
		void playBackgroundMusic();
		static void playSound(int index, bool looped = false);

	private:
#ifndef __CENTOS__
		static irrklang::ISoundEngine* engine;
#else
		void* engine;
#endif
	};
}

#endif // _Sound_H