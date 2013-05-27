// Courtesy Alan Gasperini

#ifndef TIMER_HEADER
#define TIMER_HEADER

#include <sys/time.h>

class Timer {
public:
	Timer();
	void reset();
	float getElapsedTime();
private:
	timeval cur_time;
};

inline void Timer::reset() {
	gettimeofday(&cur_time, 0);
}

#endif 
