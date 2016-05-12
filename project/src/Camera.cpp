#include "Camera.h"

#define PI 3.14159265
#define MAX_DISTANCE 50 // Pixel, which mouse can jump from one to the next call
#define RATIO_WINDOW_PLAYER 15000
#define MAX_CAMERA_DISTANCE 120
#define MIN_CAMERA_DISTANCE 5


namespace Crescer3D
{
	Camera::Camera()
	: System(SystemType::Sys_Camera)
	{
		m_lastMousePosX = 0;
		m_lastMousePosY = 0;
		m_pitch = -30;
		m_yaw = 0;
		m_rotationSensitivity = 1.0f;
		m_playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};
		m_cameraDistance = 15; // should change with player size
		m_cameraDistanceIncrement = 1;
		m_cameraDir = {-1,-1,0}; // default view ? 
		m_lookAtMatrix = IdentityMatrix();
		m_manuellView = false;
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
		m_lastMousePosX = x;
	}
	void Camera::setLastMousePosY(int y)
	{
		m_lastMousePosY= y;
	}

	mat4 Camera::getLookAtMatrix()
	{
		return m_lookAtMatrix;
	}
	vec3 Camera::getCameraDir()
	{
		return m_cameraDir;
	}
	vec3 Camera::getCameraPos()
	{
		return m_cameraPos;
	}
	void Camera::setCameraDistance(float distance)
	{
		m_cameraDistance = distance;
	}
	
	void Camera::increaseCameraDistance()
	{
		if(m_cameraDistance < MAX_CAMERA_DISTANCE)
		{
			m_cameraDistance += m_cameraDistanceIncrement;
		}

	}
	void Camera::decreaseCameraDistance()
	{
		if(m_cameraDistance > MIN_CAMERA_DISTANCE)
		{
			m_cameraDistance -= m_cameraDistanceIncrement;
		}	
	}

	void Camera::handleMouseMovement(int mousePosX, int mousePosY)
	{
		m_playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		int mouseDx = mousePosX - m_lastMousePosX;
		int mouseDy = 0;

 		if(m_manuellView)
		{
			mouseDy = m_lastMousePosY - mousePosY;
		}

		mouseDx *= m_rotationSensitivity;
		mouseDy *= m_rotationSensitivity;

		setLastMousePosX(mousePosX);
		setLastMousePosY(mousePosY);

		// don't recognize mouse jumps that are too big
		if((abs((int)mouseDx)> MAX_DISTANCE) || (abs((int)mouseDy)>MAX_DISTANCE))
		{
 			mouseDx = 0;
 			mouseDy = 0;
		}

		m_yaw += mouseDx;

		if(m_manuellView)
		{
			m_pitch += mouseDy;
		}

		//  boundaries for unusual m_pitch values
		if(m_pitch < -80.0f)
		{
			m_pitch =  -80.0f;
		}
		if(m_pitch > -5.0f)
		{
			m_pitch = -5.0f;
		}

		// limit m_pitch
		//m_pitch = -45.0f;
		
		if (m_pitch && m_yaw)
		{
			m_cameraDir.x = cos(m_pitch*PI/180) * cos(m_yaw*PI/180);
			m_cameraDir.y = sin(m_pitch*PI/180);
			m_cameraDir.z = cos(m_pitch*PI/180) * sin(m_yaw*PI/180);
			m_cameraPos = VectorSub( m_playerPos, ScalarMult( Normalize(m_cameraDir), m_cameraDistance));
		}
		CameraUpdate();
	}
	
	// Should go in player class
	void Camera::moveForwardPlayer() 
	{
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius());

		vec3 playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};
		
		vec3 cameraDirNorm = m_cameraDir;
		cameraDirNorm.y = 0;
		cameraDirNorm = Normalize(cameraDirNorm);
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();

		vec3 npp = VectorAdd(ScalarMult(cameraDirNorm, player_velocity), playerPos);

		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		m_playerPos = npp;
		CameraUpdate();
	}


	void Camera::moveBackPlayer()
	{
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius() );

		vec3 playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};
		vec3 m_cameraDirNorm = m_cameraDir;

		vec3 cameraDirNorm = Normalize(m_cameraDir);
		cameraDirNorm.y = 0; // move only in x,y plane
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();
		vec3 npp = VectorAdd(ScalarMult(cameraDirNorm, -player_velocity), playerPos);

		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		m_playerPos = npp;
		CameraUpdate();
		
	}

	void Camera::moveLeftPlayer()
	{
		
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius() );

		vec3 playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		vec3 upVector = {0, 1, 0};
		vec3 cameraDirNorm = Normalize(m_cameraDir);
		cameraDirNorm.y = 0; // move only in x,y plane
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();

		vec3 npp = VectorAdd(ScalarMult(Normalize(CrossProduct(cameraDirNorm, upVector)), -player_velocity), playerPos);
		

		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		m_playerPos = npp;
		CameraUpdate();

	}

	void Camera::moveRightPlayer () 
	{
		float player_velocity=Game::GetPlayer()->getVelocity();
		float player_radius = (Game::GetPlayer()->getRadius() );

		vec3 playerPos = {Game::GetPlayer() -> getX(), Game::GetPlayer() -> getY(), Game::GetPlayer() -> getZ()};

		vec3 upVector = {0, 1, 0};
		vec3 cameraDirNorm = Normalize(m_cameraDir);
		cameraDirNorm.y = 0; // move only in x,y plane
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();
		vec3 npp = VectorAdd(ScalarMult(Normalize(CrossProduct(cameraDirNorm, upVector)), player_velocity), playerPos);	


		if(npp.x < worldMin.x+player_radius || npp.y < worldMin.y+player_radius || npp.z < worldMin.z+player_radius || 
			npp.x > worldMax.x-player_radius || npp.y > worldMax.y-player_radius || npp.z > worldMax.z-player_radius)
			return;
		m_playerPos = npp;
		CameraUpdate();
	}

	void Camera::CameraUpdate()
	{
		Game::GetPlayer() -> setPositionX(m_playerPos.x);
		Game::GetPlayer() -> setPositionY(m_playerPos.y);
		Game::GetPlayer() -> setPositionZ(m_playerPos.z);
		
		m_cameraPos = VectorSub( m_playerPos, ScalarMult(m_cameraDir, m_cameraDistance));
		m_lookAtMatrix = lookAtv(m_cameraPos, m_playerPos, vec3(0.0f, 1.0f, 0.0f));	
		
		if(m_manuellView == false)
		{	
			float distance =  RATIO_WINDOW_PLAYER*Game::GetPlayer()->getRadius()/Window::GetWidth();
			setCameraDistance(distance);
		}
	}
	void Camera::CameraReset()
	{
		m_lookAtMatrix = IdentityMatrix();
		m_cameraPos = {0,0,0};
		m_cameraDir = {0,0,0};
	}

	void Camera::changeManuellView()
	{
		if(m_manuellView)
			m_manuellView = false;
		else
		{
			m_manuellView = true;
		}
	}

} 
