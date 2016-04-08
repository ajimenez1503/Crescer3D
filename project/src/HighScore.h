#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include "../../common/simplefont.h"
#include "System.h"
#include <string>
#include <fstream>
#include "Logger.h"
namespace Crescer3D
{
	class HighScore : public System
	{
	private:
		static int m_Score;


	public:
		HighScore();
		virtual bool Initialize();
		virtual ~HighScore();
		static void DisplayScore();
		static void IncrementScore();
		static void SaveScore(std::string name);
		static void DisplayListScores();
		static void Reset();
	};
}

#endif // _HIGHSCORE_H
