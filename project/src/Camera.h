#ifndef _Camera_H
#define _Camera_H

#include "System.h"
#include "Game.h"
#include "Sphere.h"
#include "Logger.h"
#include "../../common/VectorUtils3.h"
#include "Window.h"


namespace Crescer3D
{
	class Game;
	class Camera : public System
	{
	public:
		Camera();
		virtual ~Camera();
		virtual bool Initialize();
		static void CameraReset();
		static void CameraUpdate();
		static void setMousePosX(int x);
		static void setMousePosY(int y);
		static void setLastMousePosX(int y);
		static void setLastMousePosY(int y);
		static void handleMouseMovement(int mousePosX, int mousePosY);
		static void setCameraDistance(float distance);
		static void increaseCameraDistance();
		static void decreaseCameraDistance();
		static void changeManuellView();

		static mat4 getLookAtMatrix();
		static vec3 getCameraDir();
		static vec3 getCameraPos();

		//temporarly should go in player class:
		static void moveForwardPlayer (); 
		static void moveBackPlayer (); 
		static void moveLeftPlayer (); 
		static void moveRightPlayer (); 
		
		static void setCameraPlayerPosition(float x, float y, float z);


	private:
		static mat4 m_lookAtMatrix;
		static vec3 m_cameraPos;
		static vec3 m_cameraDir;
		static vec3 m_cameraViewDir;
		static int m_xOrigin;	
		static int m_lastMousePosX;
		static int m_lastMousePosY;
		static float m_pitch;
		static float m_yaw;
		static float m_rotationSensitivity;
		static float m_cameraDistance;
		static float m_cameraDistanceIncrement;
		static vec3 m_playerPos;
		static bool m_manuellView;

	};
}

#endif // _Camera_H
