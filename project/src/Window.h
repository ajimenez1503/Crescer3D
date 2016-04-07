#ifndef _WINDOW_H
#define _WINDOW_H

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
#include "Sphere.h"
#include "Ground.h"
#include "Game.h"
#include "Input.h"
#include "DeleteUtil.h"
#include "Logger.h"

namespace Crescer3D
{
	class Window : public System
	{
	private:
		int m_Width, m_Height;
		char* m_Title;
		static GLuint m_Program;
		static Ground m_Ground;
		static mat4 m_ProjMat;
		static bool m_CollisionState;
		static int m_Score;

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
		static void DisplayScore();
	};
}

#endif // _WINDOW_H