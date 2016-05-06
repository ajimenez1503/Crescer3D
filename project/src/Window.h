#ifndef _WINDOW_H
#define _WINDOW_H

#if defined (__LINUX__) || (__CENTOS__)
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
#include "World.h"
#include "Game.h"
#include "Input.h"
#include "DeleteUtil.h"
#include "Logger.h"
#include "Light.h"

namespace Crescer3D
{
	class World;
	
	class Window : public System
	{
	private:
		static int m_Width, m_Height;
		char* m_Title;
		static World m_World;
		static mat4 m_ProjMat;
		static mat4 m_DepthMat;
		static GLuint m_DepthBuffer;
		static GLuint m_DepthTexture;
		static GLuint m_DepthShader;
		static GLuint m_sphereShader;
		static bool m_CollisionState;

	public:
		Window(char* title, int width, int height);
		~Window();

		virtual bool Update();

		inline static int GetWidth() { return m_Width; };
		inline static int GetHeight() { return m_Height; };
		inline static GLuint GetDepthTexture() { return m_DepthTexture; };
		inline static int SetWidth(int w) { m_Width = w; };
		inline static int SetHeight(int h) { m_Height = h; };

	private:
		virtual bool Initialize();
		static void Draw();
		static void Clear();
		static void Timer(int i);
		static void InitObjects();

	};
}

#endif // _WINDOW_H
