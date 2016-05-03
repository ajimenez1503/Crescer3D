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


		mat4 getLookAtMatrix();
		vec3 getCameraDir();

		//temporarly should go in player class:
		void moveForwardPlayer (float movement_speed); 
		void moveBackPlayer (float movement_speed); 
		void moveLeftPlayer (float movement_speed); 
		void moveRightPlayer (float movement_speed); 

	private:
		mat4 lookAtMatrix;

		float cameraPosX;
		float cameraPosZ;
		float cameraPosY;
		vec3 cameraPos;
		vec3 cameraDir;
		vec3 cameraViewDir;
		int xOrigin;	
		int lastMousePosX;
		int lastMousePosY;
		float pitch;
		float yaw;
		float rotationSensitivity;
		float cameraDistance;
		float cameraDistanceIncrement;
		vec3 playerPos;

	};
}

#endif // _Camera_H