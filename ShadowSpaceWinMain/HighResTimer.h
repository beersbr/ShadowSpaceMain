#pragma once

#include <Windows.h>

class HighResTimer
{
public:
	HighResTimer(void);
	~HighResTimer(void);

	bool startTimer(void);
	double getMilliseconds(void);
	double getSeconds(void);

	bool isInitialized(void);

private:
	bool initialized;
	LARGE_INTEGER frequency;
	LARGE_INTEGER counter;
	long double frequency_value_microseconds;
	long double frequency_value_milliseconds;
	long double frequency_value_seconds;
	long long start_counter_value;
};

