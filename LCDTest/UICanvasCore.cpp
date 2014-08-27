#include "UICanvasCore.h"



bool UICanvasCore::drawSubCanvas(Canvas* sCanvas, pair<unsigned int, unsigned int>location, pair<unsigned int, unsigned int> size)
{
/*	for (int line = 0; line >= size.second; line++)
	{
		uint8_t * pagePtr = (uint8_t*)(void*)&this->lcd->page;
		memcpy(pagePtr + (4 * ((line * lcd->getWidth()) + location.second + (location.first * lcd->getWidth()))),
			sCanvas + (4 * (line*size.first)),
			size.first * 4);
	}*/
	unsigned int i = 0;
	unsigned int srcLine = 0;
	unsigned int srcCol = 0;
	unsigned int startCorner = location.first + (location.second * this->canvas->getWidth());
	for (int j = 0; j < (size.first * size.second); j++)
	{
		srcLine = j / size.first;
		unsigned int offset = (((srcLine+location.second) * (this->canvas->getWidth()))
			+(i)+location.second);
// this->canvas->getWidth();// (line*this->canvas->getWidth()) + startCorner+20;
		if (i >= size.first) i = 0;
		if (true)
		{
			this->canvas->page[offset].r = sCanvas->page[j].r;
			this->canvas->page[offset].g = sCanvas->page[j].g;
			this->canvas->page[offset].b = sCanvas->page[j].b;
			this->canvas->page[offset].a = sCanvas->page[j].a;
		}
		else
		{
			this->canvas->page[offset].r = 255;//iter->r;
			this->canvas->page[offset].g = 0;
			this->canvas->page[offset].b = 0;
			this->canvas->page[offset].a = 255;// sCanvas->page[j].a;
		}
		i++;
	}


	return true;
}