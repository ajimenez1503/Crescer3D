#include "HighScore.h"

namespace Crescer3D
{
	//bool compare (int a, int b) {return a>b;}//compara element of map

	// forward declaration of static members
	long long unsigned HighScore::m_Score;
	std::multimap<int,std::string> HighScore::map ;

	HighScore::HighScore(): System(SystemType::Sys_HighScore)
	{
		m_Score=0;
		std::multimap<int,std::string> map ();
	}

	HighScore::~HighScore()
	{
		m_Score=0;
		map.erase(map.begin(),map.end());
	}
	bool HighScore::Initialize()
	{
		sfMakeRasterFont(); // init font
		return true;
	}

	void HighScore::DisplayScore()
	{
		std::string result("Score: ");
		result = result + std::to_string(static_cast<long long unsigned>(m_Score));
		int positionx = Window::GetWidth() * 90 / 100; // 90% of the width
		int positiony = Window::GetHeight() * 5 / 100; //5% of the height
		sfDrawString(-20, 20, result.c_str());
	}

	void HighScore::IncrementScore()
	{
		m_Score++;
	}
	void HighScore::Reset()
	{
		m_Score=0;
		map.erase(map.begin(),map.end());
	}


	void HighScore::CalculateListScores()
	{
		int score=0;
		std::string line;
		std::ifstream myfile ("dataBase/Score.txt", std::ios::in );
		if (myfile.is_open())
		{
			while ( getline (myfile,line) )
			{
				//save score
				score = std::stoi(line.substr(line.find(" "),line.size()));
				//save line
				map.insert(std::pair<int,std::string>(score,line));
			}
			myfile.close();
		}
		else
		{
			Logger::Log( "Unable to open file");
		}


	}
	void HighScore::DisplayListScores()
	{
		int positionx = Window::GetWidth() * 60 / 100; // 60% of the width
		int positiony = Window::GetHeight() * 30 / 100; // 30% of the height
		sfDrawString(positionx, positiony, "Best highScore:");
		positiony+=50;
  		int limmitScores=10;//not display more than 10 lines
		if(map.size()>0){
			std::map<int,std::string>::const_iterator it = map.end();
		    do{
		        it--;
				sfDrawString(positionx, positiony, it->second.c_str());
				limmitScores--;
				positiony+=20;
		    } while (it != map.begin() && limmitScores>0);
		}
	}

	void HighScore::SaveScore(std::string name)
	{
		//TODO save only if score >0
		if(m_Score>0)
		{
			std::ofstream myfile ("dataBase/Score.txt", std::ios::out| std::ios::app );
			if (myfile.is_open() )
			{
				std::string score = std::to_string(static_cast<long long unsigned>(m_Score));
				myfile << name + std::string(" ") + score + std::string("\n");
				Logger::Log( name + std::string(" ") + score + std::string("\n") );
				myfile.close();
			}
			else
			{
				Logger::Log( "Unable to open file");
			}
		}
	}

}
