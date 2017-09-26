#pragma once
#include <vector>
#include <memory>

#include "Screen.h"

class ImageBlock
{
private:
	std::unique_ptr<CHAR_INFO[]> ptr;
	COORD size;
public:
	ImageBlock(unsigned int width, unsigned int height);
	ImageBlock(const ImageBlock&) = delete;
	ImageBlock& operator=(const ImageBlock&) = delete;

	void Render(Screen& screen, unsigned int posX, unsigned int posY);
	CHAR_INFO& operator()(unsigned int x, unsigned int y);
};

class Renderable
{
protected:
public:
	virtual ~Renderable() {}

	static void RenderBlock(Screen& screen, ImageBlock& imgBlock, unsigned int posX, unsigned int posY);
	static void RenderCharacter(Screen& screen, char value, unsigned int x, unsigned int y);
	virtual void Render(Screen& screen) const = 0;
};

void Render(Screen& screen, const std::vector<Renderable*>& thingies);