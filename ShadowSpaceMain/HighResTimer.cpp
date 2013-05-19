#include "HighResTimer.h"

HighResTimer::HighResTimer(void)
{
	initialized = QueryPerformanceFrequency(&frequency);
	if(initialized)
	{
		frequency_value_seconds = double(frequency.QuadPart);
		frequency_value_milliseconds = frequency_value_seconds/1000.0;
		frequency_value_microseconds = frequency_value_microseconds/1000.0;
	}
}

HighResTimer::~HighResTimer(void)
{
}

bool HighResTimer::startTimer(void)
{
	if(!initialized) return false;
	QueryPerformanceCounter(&counter);
	start_counter_value = counter.QuadPart;	
}

double HighResTimer::getMilliseconds(void)
{
	QueryPerformanceCounter(&counter);
	return ((double(counter.QuadPart-start_counter_value)/frequency_value_milliseconds));
}

double HighResTimer::getSeconds(void)
{
	QueryPerformanceCounter(&counter);
	return (double((counter.QuadPart-start_counter_value)/frequency_value_seconds));
}