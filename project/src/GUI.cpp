#include "GUI.h"

namespace Crescer3D
{
	// forward declaration of static members
	std::string GUI::namePlayer;
	Button GUI::buttonPlay;
	Button GUI::buttonExit;
	Button GUI::background;//it is used to create the background behind the font
	bool GUI::nameReady;

	GUI::GUI(): System(SystemType::Sys_GUI)
	{
		namePlayer="-------";//default name user
		nameReady=false;
	}

	GUI::~GUI()
	{
		namePlayer="-------";//default name user
		nameReady=false;
	}
	bool GUI::Initialize()
	{
		sfMakeRasterFont(); // init font
		mat4 m_ProjMat;
		GLuint GUIshader;
		m_ProjMat = ortho(0,800, 600, 0, -1,1);

		// Load and compile shader
		GUIshader = loadShaders("shader/shader_button.vert", "shader/shader_button.frag");
		glUseProgram(GUIshader);
		printError("Shader Init");
		glUniformMatrix4fv(glGetUniformLocation(GUIshader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);

		//define button
		buttonPlay.set("Play", GUIshader);
		buttonExit.set("Exit", GUIshader);
		background.set("", GUIshader);
		return true;
	}

	void GUI::InitView()
	{
		background.setPositionSize( 70 ,50 ,100,200);//postion 670% of the width and 50% of the height
		background.Draw();
		HighScore::DisplayListScores();

		buttonExit.setPositionSize(25,30,100,75);
		buttonExit.Draw();
		if(buttonExit.isClick()){// move to Game_GameOver when click on Exit
			Engine::GetEngine()->SetEngineState(ShuttingDown);
		}

		//move to Game_Play when click on play
		buttonPlay.setPositionSize(25,70,100,75);
		buttonPlay.Draw();
		//TODO set initial position of Player
		if(buttonPlay.isClick()){
			Game::SetGameStatePlay();
		}
	}

	void GUI::PlayView()
	{
		background.setPositionSize( 93 ,5 ,50,20);//postion 93% of the width and 5% of the height
		background.Draw();
		HighScore::DisplayScore();

		buttonExit.setPositionSize(5,5,30,20);
		buttonExit.Draw();
		if(buttonExit.isClick()){// move to Game_GameOver when click on Exit
			Game::SetGameStateGameOver();
		}
	}

	void GUI::GameOverView()
	{
		int positionx=Window::GetWidth()*40 /100;//40% of the width
		int positiony=Window::GetHeight()*50 /100;//50% of the height

		buttonExit.setPositionSize(30,25,80,60);
		buttonExit.Draw();
		//save score and name
		//move to Game_Play when click on play
		buttonPlay.setPositionSize(70,25,80,60);
		buttonPlay.Draw();

		if(nameReady)
		{
			background.setPositionSize( 50 ,50 ,90,40);//postion 50% of the width and 50% of the height
			background.Draw();
			//display name
			sfDrawString(positionx,positiony, "HighScore saved");
			if(buttonExit.isClick()){// move to Game_GameOver when click on Exit
				HighScore::SaveScore(namePlayer);
				Engine::GetEngine()->SetEngineState(ShuttingDown);
			}

			//set initial position of Player
			if(buttonPlay.isClick()){
				HighScore::SaveScore(namePlayer);
				namePlayer="-------";//default name user
				nameReady=false;
				Input::Reset();
				Game::SetGameStateInit();
			}
		}
		else
		{
			background.setPositionSize( 50 ,55 ,90,55);//postion 50% of the width and 55% of the height
			background.Draw();

			//display name
			sfDrawString(positionx,positiony, "Write your name: ");
			positiony+=50;
			positionx+=50;
			sfDrawString(350,350, namePlayer.c_str());
			glutKeyboardFunc(ReadName);
			//READ name until there are 7 character

			if(buttonExit.isClick()){// move to Game_GameOver when click on Exit
				Engine::GetEngine()->SetEngineState(ShuttingDown);
			}

			//TODO set initial position of Player
			if(buttonPlay.isClick()){
				namePlayer="-------";//default name user
				Input::Reset();
				Game::SetGameStateInit();
			}
		}

	}

		/*----------------------------------------------------------------------------------------
	 *	\brief	This function is used to see if a mouse click or event is within a button
	 *			client area.
	 *	\param	x	-	the x coord to test
	 *	\param	y	-	the y-coord to test
	 */
	void GUI::positionClickMouse(int x_pos,int y_pos)
	{
		if(Game::IsStateGameOver())
		{
			buttonPlay.ClickTest(x_pos,y_pos);
			buttonExit.ClickTest(x_pos,y_pos);
		}
		else if(Game::IsStateInit())
		{
			buttonPlay.ClickTest(x_pos,y_pos);
			buttonExit.ClickTest(x_pos,y_pos);
		}
		else if(Game::IsStatePlay())
		{
			buttonExit.ClickTest(x_pos,y_pos);
		}
	}


	void GUI::ReadName(unsigned char key, int xx, int yy)
	{
		if(key==GLUT_KEY_RETURN)
		{
			if(NameIsReady()){
				nameReady=true;
			}
			else{
				std::size_t found = namePlayer.find("-");
				std::size_t length = namePlayer.size()-found;
				if (found!=std::string::npos)
				{
					namePlayer.replace (found, length, length, ' ');
				}
			}

		}
		else if((key>='a' && key<='z') || (key==' ') || (key>='A' && key<='Z'))
		{
			std::size_t found = namePlayer.find("-");
			if (found!=std::string::npos)
			{
				namePlayer.replace (found,  1,  1, key);
			}
		}
	}

	//return true if there arent any "-" o on the name
	bool GUI::NameIsReady()
	{
		return std::string::npos==namePlayer.find("-");
	}

}
