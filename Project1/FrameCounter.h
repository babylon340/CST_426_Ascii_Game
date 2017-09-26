#pragma once
#include <Windows.h>

class FrameCounter
{
private:
	double frameOffset;
	LARGE_INTEGER nextTime;
	LARGE_INTEGER frequency;
public:
	FrameCounter(unsigned int framesPerSecond) : frameOffset(1.0 / framesPerSecond)
	{
		QueryPerformanceFrequency(&frequency);
	}

	void startTimer()
	{
		QueryPerformanceCounter(&nextTime);
		nextTime.QuadPart = frequency.QuadPart * (nextTime.QuadPart / frequency.QuadPart + frameOffset);
	}
	bool inNextFrame() const
	{
		LARGE_INTEGER thisTime;
		QueryPerformanceCounter(&thisTime);
		return thisTime.QuadPart >= nextTime.QuadPart;
	}
	void triggerNextFrame()
	{
		startTimer();
	}
};