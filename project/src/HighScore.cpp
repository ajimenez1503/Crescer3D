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
		sfDrawString(20, 20, result.c_str());
	}

	void HighScore::IncrementScore()
	{
		m_Score++;
	}

}
