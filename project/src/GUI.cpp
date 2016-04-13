#include "GUI.h"

namespace Crescer3D
{
	// forward declaration of static members
	std::string GUI::namePlayer;
	Button GUI::buttonPlay;
	Button GUI::buttonExit;


	GUI::GUI(): System(SystemType::Sys_GUI)
	{
		namePlayer="-------";//default name user
	}

	GUI::~GUI()
	{
		namePlayer="-------";//default name user
	}
	bool GUI::Initialize()
	{
		sfMakeRasterFont(); // init font
		//shader to button
		GLuint Program;
		mat4 m_ProjMat;
		m_ProjMat = ortho(0,800, 600, 0, -1,1);

		// Load and compile shader
		Program = loadShaders("shader/shader_button.vert", "shader/shader_button.frag");
		glUseProgram(Program);
		printError("Shader Init");
		glUniformMatrix4fv(glGetUniformLocation((Program), "projMatrix"), 1, GL_TRUE, m_ProjMat.m);


		//define button
		buttonPlay.set("Play",Program);
		buttonExit.set("Exit",Program);
		return true;
	}

	void GUI::InitView()
	{
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
		HighScore::DisplayScore();

		buttonExit.setPositionSize(5,5,30,20);
		buttonExit.Draw();
		if(buttonExit.isClick()){// move to Game_GameOver when click on Exit
			Game::SetGameStateGameOver();
		}
	}

	void GUI::GameOverView()
	{
		buttonExit.setPositionSize(30,25,80,60);
		buttonExit.Draw();
		if(buttonExit.isClick()){// move to Game_GameOver when click on Exit
			Engine::GetEngine()->SetEngineState(ShuttingDown);
		}

		//move to Game_Play when click on play
		buttonPlay.setPositionSize(70,25,80,60);
		buttonPlay.Draw();
		//TODO set initial position of Player
		if(buttonPlay.isClick()){
			Game::SetGameStateInit();
		}


		//save score and name
		if(NameIsReady())
		{
			HighScore::SaveScore(namePlayer);
			Engine::GetEngine()->SetEngineState(ShuttingDown);
		}

		//display name
		sfDrawString(300,300, "Write your name: ");
		sfDrawString(350,350, namePlayer.c_str());
		glutKeyboardFunc(ReadName);
		//READ name until there are 7 character

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
		if((key>='a' && key<='z') || (key==' ') || (key>='A' && key<='Z'))
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