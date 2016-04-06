#ifndef _WINDOW_H
#define _WINDOW_H

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

#include "../../common/GL_utilities.h"
#include "../../common/loadobj.h"
#include "../../common/VectorUtils3.h"
#include "../../common/LoadTGA.h"
#include "../../common/simplefont.h"

#include <iostream>
#include "System.h"
#include "deleteutil.h"
#include "sphere.h"
#include "ground.h"

namespace Crescer3D
{
	class Window : public System
	{
	private:
		int m_Width, m_Height;
		char* m_Title;
		static GLuint m_Program;
		static Sphere m_Player;
		static Sphere m_Enemy;
		static Ground m_Ground;
		static mat4 m_ProjMat;

	public:
		Window(char* title, int width, int height);
		~Window();

		virtual bool Update();
		

		inline int GetWidth() { return m_Width; };
		inline int GetHeight() { return m_Height; };

	private:
		virtual bool Initialize();
		static void Draw();
		static void Clear();
		static void Timer(int i);
		void displayScore();
	};
}

#endif // _WINDOW_H