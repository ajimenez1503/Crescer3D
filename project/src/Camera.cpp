#include "Camera.h"

#define PI 3.14159265
#define MAX_DISTANCE 50 // Pixel, which mouse can jump from one to the next call

namespace Crescer3D
{
	Camera::Camera()
	: System(SystemType::Sys_Camera)
	{
		lastMousePosX = 0;
		lastMousePosY = 0;
		pitch = 0;
		yaw = 0;
		rotationSensitivity = 1.0f;
		playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};
		cameraDistance = 10; // should change with player size
		cameraDistanceIncrement = 1;
		cameraDir = {-1,-1,0}; // default view ? 
		lookAtMatrix = IdentityMatrix();
	}

	Camera::~Camera()
	{
	}

	bool Camera::Initialize()
	{
		//Logger::Log("Hello Camera!");
		return true;
	}

	void Camera::setLastMousePosX(int x)
	{
		lastMousePosX = x;
	}
	void Camera::setLastMousePosY(int y)
	{
		lastMousePosY= y;
	}

	mat4 Camera::getLookAtMatrix()
	{
		return lookAtMatrix;
	}
	vec3 Camera::getCameraDir()
	{
		return cameraDir;
	}
	vec3 Camera::getCameraPos()
	{
		return cameraPos;
	}
	void Camera::setCameraDistance(float distance)
	{
		cameraDistance = distance;
	}
	
	void Camera::increaseCameraDistance()
	{
		cameraDistance += cameraDistanceIncrement;
	}
	void Camera::decreaseCameraDistance()
	{
		cameraDistance -= cameraDistanceIncrement;
	}

	void Camera::handleMouseMovement(int mousePosX, int mousePosY)
	{
		playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		int mouseDx = mousePosX - lastMousePosX;
		int mouseDy = lastMousePosY - mousePosY;

		mouseDx *= rotationSensitivity;
		mouseDy *= rotationSensitivity;

		setLastMousePosX(mousePosX);
		setLastMousePosY(mousePosY);

		// don't recognize mouse jumps that are too big
		if((abs((int)mouseDx)> MAX_DISTANCE) || (abs((int)mouseDy)>MAX_DISTANCE))
		{
 			mouseDx = 0;
 			mouseDy = 0;
		}

		yaw += mouseDx;
		pitch += mouseDy;

		//  boundaries for unusual pitch values
		if(pitch < -80.0f)
		{
			pitch =  -80.0f;
		}
		if(pitch > -5.0f)
		{
			pitch = -5.0f;
		}

		// limit pitch
		//pitch = -45.0f;
		
		if (pitch && yaw)
		{
			cameraDir.x = cos(pitch*PI/180) * cos(yaw*PI/180);
			cameraDir.y = sin(pitch*PI/180);
			cameraDir.z = cos(pitch*PI/180) * sin(yaw*PI/180);
			cameraDir = Normalize(cameraDir);
			cameraPos = VectorSub( playerPos, ScalarMult(cameraDir, cameraDistance));
		}
		CameraUpdate();

		//cameraPos.x = playerPosX - cameraDir.x * cameraDistance;
		//cameraPos.y = playerPosY - cameraDir.y * cameraDistance;
		//cameraPos.z = playerPosZ - cameraDir.z * cameraDistance;

	/*
		int mousedx = 100;
		int windowCenterX = 300;
		int windowCenterY = 300;
		if(mousePosX > windowCenterX+mousedx || mousePosX < windowCenterX-mousedx || mousePosY > windowCenterY+mousedx || mousePosY < windowCenterY-mousedx)
		{   
			glutWarpPointer( windowCenterX, windowCenterY );
		}

*/
	}
	
	// Should go in player class
	void Camera::moveForwardPlayer() 
	{
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius() * 2);
		playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		vec3 cameraDirNorm = Normalize(cameraDir);
		cameraDirNorm.y = 0; // move only in x,y plane
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();

		vec3 npp = VectorAdd(ScalarMult(cameraDirNorm, player_velocity), playerPos);

		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		playerPos = npp;
		CameraUpdate();
	}

	void Camera::moveBackPlayer()
	{
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius() * 2);
		playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		vec3 cameraDirNorm = Normalize(cameraDir);
		cameraDirNorm.y = 0; // move only in x,y plane
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();
		vec3 npp = VectorAdd(ScalarMult(cameraDirNorm, -player_velocity), playerPos);

		
		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		playerPos = npp;
		CameraUpdate();
	}
	void Camera::moveLeftPlayer()
	{
		
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius() * 2);
		playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		vec3 upVector = {0, 1, 0};
		vec3 cameraDirNorm = Normalize(cameraDir);
		cameraDirNorm.y = 0; // move only in x,y plane
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();
		vec3 npp = VectorAdd(ScalarMult(Normalize(CrossProduct(cameraDirNorm, upVector)), -player_velocity), playerPos);
		
		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		playerPos = npp;
		CameraUpdate();
	}

	void Camera::moveRightPlayer () 
	{
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius() * 2);
		playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		vec3 upVector = {0, 1, 0};
		vec3 cameraDirNorm = Normalize(cameraDir);
		cameraDirNorm.y = 0; // move only in x,y plane
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();
		vec3 npp = VectorAdd(ScalarMult(Normalize(CrossProduct(cameraDirNorm, upVector)), player_velocity), playerPos);	

		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		playerPos = npp;
		CameraUpdate();
	}

	void Camera::CameraUpdate()
	{
		Game::GetPlayer() -> setPositionX(playerPos.x);
		Game::GetPlayer() -> setPositionY(playerPos.y);
		Game::GetPlayer() -> setPositionZ(playerPos.z);
		
		cameraPos = VectorSub( playerPos, ScalarMult(cameraDir, cameraDistance));
		lookAtMatrix = lookAtv(cameraPos, playerPos, vec3(0.0f, 1.0f, 0.0f));	
	}
	void Camera::CameraReset()
	{
		lookAtMatrix = IdentityMatrix();
		cameraPos = {0,0,0};
		cameraDir = {0,0,0};
	}
} 
