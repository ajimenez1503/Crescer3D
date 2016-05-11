#include "Timing.h"

namespace Crescer3D
{	
	unsigned long Timing::m_StartTime;

	unsigned long Timing::GetWorldSeconds()
	{
		timespec t;
		#ifdef __OSX__
			clock_serv_t cclock;
			mach_timespec_t mts;
			host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
			clock_get_time(cclock, &mts);
			mach_port_deallocate(mach_task_self(), cclock);
			t.tv_sec = mts.tv_sec;
			t.tv_nsec = mts.tv_nsec;
		#else
			//clock_gettime(CLOCK_REALTIME, &t);
		#endif
	
		return t.tv_sec;
	}

	unsigned long Timing::GetGameSeconds()
	{
		return GetWorldSeconds() - m_StartTime;
	}

	void Timing::SetStartTime()
	{
		m_StartTime = GetWorldSeconds();
	}
}
