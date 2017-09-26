#include "Screen.h"

void PrintError(DWORD err)
{
	char* temp = nullptr;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, NULL, reinterpret_cast<char*>(&temp), 0, NULL);
	MessageBox(NULL, temp, "Error", MB_OK);
	LocalFree(temp);
}

Screen::Screen() : original(GetStdHandle(STD_OUTPUT_HANDLE)),
	usingFront(true)
{
	CONSOLE_SCREEN_BUFFER_INFO bufferData;

	buffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	buffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(buffers[!usingFront]);

	GetConsoleScreenBufferInfo(original, &bufferData);
	windowSize.X = bufferData.srWindow.Right - bufferData.srWindow.Left + 1;
	windowSize.Y = bufferData.srWindow.Bottom - bufferData.srWindow.Top + 1;
}
Screen::~Screen()
{
	SetConsoleActiveScreenBuffer(original);
}

COORD Screen::GetSize() const
{
	return windowSize;
}

void Screen::swap()
{
	DWORD burn;
	SetConsoleActiveScreenBuffer(buffers[usingFront]);
	FillConsoleOutputCharacter(buffers[!usingFront], 0, windowSize.X*windowSize.Y, { 0, 0 }, &burn);
	usingFront = !usingFront;
}

Screen::operator HANDLE()
{
	return buffers[usingFront];
}