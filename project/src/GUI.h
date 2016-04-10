#ifndef _GUI_H
#define _GUI_H

#include "Platform.h"

#ifdef __LINUX__
	extern "C"
	{
		#include <GL/gl.h>
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

#include "../../common/simplefont.h"
#include "System.h"
#include <string>
#include "Logger.h"
#include "Window.h"
#include "HighScore.h"
namespace Crescer3D
{
	class GUI : public System
	{
	private:
		static std::string namePlayer;
		static bool NameIsReady();
		static void ReadName(unsigned char key, int xx, int yy);
	public:
		GUI();
		virtual bool Initialize();
		virtual ~GUI();
		static void GameOverView();
		static void InitView();
		static void PlayView();
	};
}

#endif // _GUI_H
