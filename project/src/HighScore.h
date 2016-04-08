#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include "../../common/simplefont.h"
#include "System.h"
#include<stdio.h>
#include <string>
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
	};
}

#endif // _HIGHSCORE_H
