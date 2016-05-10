#ifndef _Camera_H
#define _Camera_H

#include "System.h"
#include "Game.h"
#include "Sphere.h"
#include "Logger.h"
#include "../../common/VectorUtils3.h"


namespace Crescer3D
{
	class Game;
	class Camera : public System
	{
	public:
		Camera();
		virtual ~Camera();
		virtual bool Initialize();
		void CameraReset();
		void CameraUpdate();
		void setMousePosX(int x);
		void setMousePosY(int y);
		void setLastMousePosX(int y);
		void setLastMousePosY(int y);
		void handleMouseMovement(int mousePosX, int mousePosY);
		void setCameraDistance(float distance);
		void increaseCameraDistance();
		void decreaseCameraDistance();
		void changeManuellView();

		mat4 getLookAtMatrix();
		vec3 getCameraDir();
		vec3 getCameraPos();

		//temporarly should go in player class:
		void moveForwardPlayer (float movement_speed); 
	//	void moveBackPlayer (float movement_speed); 
	//	void moveLeftPlayer (float movement_speed); 
	//	void moveRightPlayer (float movement_speed); 

	private:
		mat4 m_lookAtMatrix;
		vec3 m_cameraPos;
		vec3 m_cameraDir;
		vec3 m_cameraViewDir;
		int m_xOrigin;	
		int m_lastMousePosX;
		int m_lastMousePosY;
		float m_pitch;
		float m_yaw;
		float m_rotationSensitivity;
		float m_cameraDistance;
		float m_cameraDistanceIncrement;
		vec3 m_playerPos;
		bool m_manuellView;

	};
}

#endif // _Camera_H