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
		//TODO improve with gcc11
		// needs to be fixed: get score data from gameplay subsytem
		int score = m_Score;

		char outString[28]; // enough to hold all numbers up to 64-bits and "Score: "
		const char* a = "Score: ";
		sprintf(outString,"%s%d",a,score);
		sfDrawString(20, 20, outString);
	}

	void HighScore::IncrementScore()
	{
		m_Score++;
	}

}
