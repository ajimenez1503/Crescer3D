#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#if defined (__LINUX__) || (__CENTOS__)
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __OSX__
	extern "C"
	{
		#include <OpenGL/gl3.h>
		#include "../../common/mac/MicroGlut.h"
	}
#endif

#include <string>
#include <fstream>
#include <map>
#include "../../common/simplefont.h"
#include "System.h"
#include "Window.h"
#include "Logger.h"


namespace Crescer3D
{
	class HighScore : public System
	{
	private:
		static long long unsigned m_Score;
		static std::multimap<int,std::string> map;


	public:
		HighScore();
		virtual bool Initialize();
		virtual ~HighScore();
		static void DisplayScore();
		static void IncrementScore();
		static void SaveScore(std::string name);
		static void CalculateListScores();
		static void DisplayListScores();
		static void Reset();
	};
}

#endif // _HIGHSCORE_H
