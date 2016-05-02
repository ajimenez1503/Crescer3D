#ifndef _WINDOW_H
#define _WINDOW_H

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

#include "HighScore.h"
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
		static GLuint m_stdShader;
		static GLuint m_sphereShader;
		static GLuint m_groundShader;
		static Ground m_Ground;
		static mat4 m_ProjMat;
		static bool m_CollisionState;
		static vec3 m_lightDirection;

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

	};
}

#endif // _WINDOW_H
