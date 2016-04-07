#ifndef _INPUT_H
#define _INPUT_H

#include "Platform.h"

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

#include "System.h"
#include "Game.h"
#include "Engine.h"
#include "../../common/VectorUtils3.h"


namespace Crescer3D
{
	class Input : public System
	{
	public:
		Input();
		virtual ~Input();

		virtual bool Update();
		static inline mat4 GetLookAtMatrix() { return m_LookAtMatrix; }
		static vec2 GetMousePosition();

	private:
		static void Keyboard(unsigned char key, int xx, int yy);
		static void MouseButton(int button, int state, int x, int y);
		static void MouseMove(int x, int y);

		// camera steering parameters
		// should be moved into the camera class later
		static mat4 m_LookAtMatrix;
		static float m_CameraAngle;
		static float m_CameraDirX;
		static float m_CameraDirZ;
		static float m_CameraPosX;
		static float m_CameraPosZ;
		static float m_CameraPosY;
		static float m_DeltaAngle;
		static int m_xOrigin;
		static int m_MouseXPos;
		static int m_MouseYPos;
	};
}

#endif // _INPUT_H