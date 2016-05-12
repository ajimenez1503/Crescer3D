#include "Input.h"

namespace Crescer3D
{
	// forward declaration of static members
	
	int   Input::m_MouseXPos;
	int   Input::m_MouseYPos;

	Input::Input()
		: System(SystemType::Sys_Input)
	{	
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
		{/*
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
				Game::GetCamera()->moveForwardPlayer();
			break;
			case 's' :
				Game::GetCamera()->moveBackPlayer();
			break;
			case 'a' :
				Game::GetCamera()->moveLeftPlayer();
			break;
			case 'd' :
				Game::GetCamera()->moveRightPlayer();
			break;
			*/
			case 'a' :
				Game::GetCamera()->changeManuellView();
			break;
			case 's' :
				Game::GetCamera()->increaseCameraDistance();
			break;
			case 'd' :
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
		/*
		if(Game::IsStatePlay())
		{
			float velocity = 0.5f;
			Game::GetCamera()->moveForwardPlayer();			
		}
		*/
		return true;
	}
}
