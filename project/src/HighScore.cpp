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

	void HighScore::IncrementScore(int score)
	{
		m_Score=m_Score+score;
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
				score = std::stoi(line.substr(line.find("  "),line.size()));
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
		positionx+=20;
  		int position=1;//not display more than 10 lines
		std::string line;
		if(map.size()>0){
			std::map<int,std::string>::const_iterator it = map.end();
		    do{
		        it--;
				if(position>=10){
					line = std::to_string(static_cast<long long unsigned>(position)) + ". "+ it->second  ;
				}
				else{
					line = std::to_string(static_cast<long long unsigned>(position)) + ".  "+ it->second  ;
				}
				sfDrawString(positionx, positiony, line.c_str());
				position++;
				positiony+=20;
		    } while (it != map.begin() && position<=10);
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
				myfile << name + std::string("  ") + score + std::string("\n");
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
