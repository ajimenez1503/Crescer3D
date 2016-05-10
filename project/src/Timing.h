#ifndef _TIMING_H
#define _TIMING_H

#include <time.h>
#include <sys/time.h>
#ifdef __OSX__
	#include <mach/clock.h>
	#include <mach/mach.h>
#endif

namespace Crescer3D
{
	class Timing
	{	
	public:
		static unsigned long GetWorldSeconds();
		static unsigned long GetGameSeconds();
		static void SetStartTime();
	private:
		static unsigned long m_StartTime;
	};
}

#endif // _TIMING_H