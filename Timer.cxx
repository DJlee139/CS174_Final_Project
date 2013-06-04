#include "Timer.h"

Timer::Timer() {
	gettimeofday(&cur_time, 0);
}

float Timer::getElapsedTime() {
	float dif;
	timeval newtime;
	gettimeofday(&newtime, 0);
	dif=(newtime.tv_sec-cur_time.tv_sec);
	dif+=(newtime.tv_usec-cur_time.tv_usec)/1000000.0;
	return dif;
}