#include "HighScore.h"

namespace Crescer3D
{
	// forward declaration of static members
	int HighScore::m_Score;

	HighScore::HighScore(): System(SystemType::Sys_HighScore)
	{
		m_Score=0;
	}

	HighScore::~HighScore()
	{
		m_Score=0;
	}
	bool HighScore::Initialize()
	{
		sfMakeRasterFont(); // init font
		return true;
	}

	void HighScore::DisplayScore()
	{
		//with C++11
		std::string result = "Score: ";
		result = result + std::to_string(m_Score);
		sfDrawString(-20, 20, result.c_str());
	}

	void HighScore::IncrementScore()
	{
		m_Score++;
	}
	void HighScore::Reset()
	{
		m_Score=0;
	}

	bool compare (int a, int b) {return a>b;}//compara element of map

	void HighScore::DisplayListScores()
	{

		bool(*fn_pt)(int,int) = compare;
		std::multimap<int,std::string,bool(*)(int,int)> map (fn_pt); // function pointer as comp;

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


		int positionx=500;
  		int positiony=200;
		sfDrawString(positionx, positiony, "Best highScore:");
		positiony+=50;
  		int limmitScores=10;//not display more than 10 lines
		for (std::map<int,std::string>::const_iterator it = map.begin(); it != map.end() && limmitScores>0; it++) {
			sfDrawString(positionx, positiony, it->second.c_str());
			limmitScores--;
			positiony+=20;
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
				myfile << name+" "+std::to_string(m_Score)+"\n";
				Logger::Log( name+" "+std::to_string(m_Score)+"\n");
				myfile.close();
			}
			else
			{
				Logger::Log( "Unable to open file");
			}
		}

	}

}
