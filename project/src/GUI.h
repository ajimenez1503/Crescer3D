#ifndef _GUI_H
#define _GUI_H

#ifdef __LINUX__
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

#include "../../common/simplefont.h"
#include "System.h"
#include <string>
#include "Logger.h"
#include "Window.h"
#include "HighScore.h"
#include "Button.h"
#include "Input.h"

namespace Crescer3D
{
	class Button;

	class GUI : public System
	{
	private:
		static std::string namePlayer;
		static Button buttonPlay;
		static Button buttonExit;

		static bool NameIsReady();
		static void ReadName(unsigned char key, int xx, int yy);

	public:
		GUI();
		virtual bool Initialize();
		virtual ~GUI();
		static void GameOverView();
		static void InitView();
		static void PlayView();
		static void positionClickMouse(int x_pos,int y_pos);
	};
}

#endif // _GUI_H
