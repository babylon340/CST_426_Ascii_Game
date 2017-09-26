#include "Renderable.h"

ImageBlock::ImageBlock(unsigned int width, unsigned int height) : ptr(new CHAR_INFO[width * height]),
	size{ static_cast<SHORT>(width), static_cast<SHORT>(height) }
{
}
void ImageBlock::Render(Screen& screen, unsigned int posX, unsigned int posY)
{
	SMALL_RECT rect = { static_cast<SHORT>(posX), static_cast<SHORT>(posY),
		static_cast<SHORT>(posX + size.X), static_cast<SHORT>(posY + size.Y) };
	WriteConsoleOutput(screen, ptr.get(), size, { 0, 0 }, &rect);
}
CHAR_INFO& ImageBlock::operator()(unsigned int x, unsigned int y)
{
	if (static_cast<SHORT>(x) >= size.X || static_cast<SHORT>(y) >= size.Y)
	{
		OutputDebugString(TEXT("Out of Bounds Access"));
	}
	return ptr[x + size.X * y];
}

void Renderable::RenderBlock(Screen& screen, ImageBlock& imgBlock, unsigned int posX, unsigned int posY)
{
	imgBlock.Render(screen, posX, posY);
}
void Renderable::RenderCharacter(Screen& screen, char value, unsigned int x, unsigned int y)
{
	if (x >= 0 && x < screen.GetSize().X && y >= 0 && y < screen.GetSize().Y)
	{
		DWORD burn;
		SetConsoleCursorPosition(screen, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
		WriteConsole(screen, &value, 1, &burn, NULL);
	}
}

void Render(Screen& screen, const std::vector<Renderable*>& thingies)
{
	for (std::vector<Renderable*>::const_iterator itr = thingies.cbegin();
		itr != thingies.cend(); ++itr)
	{
		(*itr)->Render(screen);
	}
}