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

	//return true if there arent any "-" o on the name
	bool GUI::NameIsReady()
	{
		return std::string::npos==namePlayer.find("-");
	}


	void GUI::GameOverView()
	{
		buttonPlay.setPosition(40,30);
		buttonPlay.Draw();
		//TODO set initial position of Player
			//Game::SetGameStatePlay();


		//TODO move to exit when click on exit
		buttonExit.setPosition(40,80);
		buttonExit.Draw();
			//Engine::GetEngine()->SetEngineState(ShuttingDown);
		//save score and name
		if(NameIsReady())
		{
			HighScore::SaveScore(namePlayer);
			Engine::GetEngine()->SetEngineState(ShuttingDown);
		}


		//display name
		sfDrawString(300,150, "Write your name: ");
		sfDrawString(300,200, namePlayer.c_str());
		glutKeyboardFunc(ReadName);
		//READ name until there are 7 character



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

	void GUI::InitView()
	{

		HighScore::DisplayListScores();

		//TODO move to Game_Play when click on play
		buttonPlay.setPosition(40,30);
		buttonPlay.Draw();
		//TODO set initial position of Player
		Game::SetGameStatePlay();

		buttonExit.setPosition(40,80);
		buttonExit.Draw();
		//TODO move to Game_GameOver when click on Exit
			//SetGameStateGameOver();
	}

	void GUI::PlayView()
	{
		HighScore::DisplayScore();

		//TODO move to Game_GameOver when click on Exit
		buttonExit.setPosition(40,30);
		buttonExit.Draw();
			//SetGameStateGameOver();
	}

}
