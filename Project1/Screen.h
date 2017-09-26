#pragma once
#include <Windows.h>

void PrintError(DWORD err);

class Screen
{
private:
	HANDLE original;
	HANDLE buffers[2];
	bool usingFront;
	COORD windowSize;
public:
	Screen();
	~Screen();

	COORD GetSize() const;
	void swap();
	operator HANDLE();
};