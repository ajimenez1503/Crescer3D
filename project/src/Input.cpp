#include "Input.h"

namespace Crescer3D
{
	// forward declaration of static members
	
	int   Input::m_xOrigin;
	int   Input::m_MouseXPos;
	int   Input::m_MouseYPos;

	Input::Input()
		: System(SystemType::Sys_Input)
	{	
		m_xOrigin = -1;
		m_MouseXPos = 0;
		m_MouseYPos = 0;
		glutMouseFunc(MouseButton);
		glutMotionFunc(MouseMove);
		glutKeyboardFunc(Keyboard);
		//glutPassiveMotionFunc(&MouseMove); // set up mouse movement.
	}

	bool Input::Initialize()
	{
		return true;
	}

	void Input::Reset()
	{

		m_xOrigin = -1;
		m_MouseXPos = 0;
		m_MouseYPos = 0;
		glutMouseFunc(MouseButton);
		glutMotionFunc(MouseMove);
		glutKeyboardFunc(Keyboard);
	}

	Input::~Input()
	{
	}

	void Input::MouseButton(int button, int state, int x, int y)
	{
		// only start motion if the left button is pressed
		if (button == GLUT_LEFT_BUTTON)
		{
			//check button
			GUI::positionClickMouse(x,y);

/*
			// when the button is released
			if (state == GLUT_UP)
			{
				m_CameraAngle += m_DeltaAngle;
				m_xOrigin = -1;
			}
			else // state = GLUT_DOWN
				m_xOrigin = x;
				*/
		}
	}

	void Input::MouseMove(int x, int y)
	{
		Game::GetCamera() -> handleMouseMovement(x,y);
	}

	vec2 Input::GetMousePosition()
	{
		return vec2(m_MouseXPos, m_MouseYPos);
	}

	void Input::Keyboard(unsigned char key, int xx, int yy)
	{
		float fraction = 0.1f;
		float velocity = 0.5f;

		switch (key)
		{
			case GLUT_KEY_UP :
				Game::GetPlayer()->moveForward();
			break;
			case GLUT_KEY_LEFT :
				Game::GetPlayer()->moveLeft();
			break;
			case GLUT_KEY_RIGHT :
				Game::GetPlayer()->moveRight();
			break;
			case GLUT_KEY_DOWN :
				Game::GetPlayer()->moveBack();
			break;
			case 'w' :
				Game::GetCamera()->moveForwardPlayer(velocity);
			break;
			case 's' :
				Game::GetCamera()->moveBackPlayer(velocity);
			break;
			case 'a' :
				Game::GetCamera()->moveLeftPlayer(velocity);
			break;
			case 'd' :
				Game::GetCamera()->moveRightPlayer(velocity);
			break;
			case 'n' :
				Game::GetCamera()->increaseCameraDistance();
			break;
			case 'm' :
				Game::GetCamera()->decreaseCameraDistance();
			break;
			case '1' :
				Sound::playSound(1);
			break;
			case '2' :
				Sound::playSound(2);
			break;
			case 'q' :
			case 'Q' :
			case GLUT_KEY_ESC:
				Game::GameOver();
			break;
		}
	}


	bool Input::Update()
	{
		return true;
	}
}
