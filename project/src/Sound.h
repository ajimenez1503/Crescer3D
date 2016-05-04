#ifndef _Sound_H
#define _Sound_H

#include "System.h"
#include "Logger.h"
#include "../../irrKlang/include/irrKlang.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


namespace Crescer3D
{
	class Sound : public System
	{
	public:
		Sound();
		virtual ~Sound();
		virtual bool Initialize();
		static void playSound(int index);

	private:
		static irrklang::ISoundEngine* engine;
	};
}

#endif // _Sound_H