#include "GUI.h"

namespace Crescer3D
{
	// forward declaration of static members
	std::string GUI::namePlayer;

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
		return true;
	}

	//return true if there arent any "-" o on the name
	bool GUI::NameIsReady()
	{
		return std::string::npos==namePlayer.find("-");
	}


	void GUI::GameOverView()
	{
		//save score and name
		if(NameIsReady())
		{
			HighScore::SaveScore(namePlayer);
			Engine::GetEngine()->SetEngineState(ShuttingDown);
		}
		//TODO display button
			//TODO move to Game_Play when click on play
				//Game::SetGameStatePlay();
			//TODO display button exit and close game
				//Engine::GetEngine()->SetEngineState(ShuttingDown);

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
		//TODO set initial position of Player

		Game::SetGameStatePlay();
		//TODO move to Game_GameOver when click on Exit
		//SetGameStateGameOver();
	}

	void GUI::PlayView()
	{
		HighScore::DisplayScore();
		//TODO move to Game_GameOver when click on Exit
		//SetGameStateGameOver();
	}

}
