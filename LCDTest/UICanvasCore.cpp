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
		unsigned int offset, xRel, yRel = 0;
		yRel = srcLine;
		xRel = j - (yRel*size.first);

		offset = (xRel + (yRel*this->canvas->getWidth()));

		if (i >= size.first) i = 0;
		if (sCanvas->page[j].a != 0)
		{
			this->canvas->page[offset].r = sCanvas->page[j].r;
			this->canvas->page[offset].g = sCanvas->page[j].g;
			this->canvas->page[offset].b = sCanvas->page[j].b;
			this->canvas->page[offset].a = sCanvas->page[j].a;
		}
		else
		{
			if (this->canvas->page[offset].a == 0)
			{
				this->canvas->page[offset].r = 127;
				this->canvas->page[offset].g = 0;
				this->canvas->page[offset].b = 127;
				this->canvas->page[offset].a = 255;
			}
			else //basic transparancy handling
			{
				//this->canvas->page[offset].b = (this->canvas->page[offset].b * this->canvas->page[offset].a) +
				//	(sCanvas->page[j].a * sCanvas->page[j].b * (1 - this->canvas->page[offset].a));
				//this->canvas->page[offset].a = 255;

				this->canvas->page[offset] = blendPixel(sCanvas->page[j], this->canvas->page[offset]);
			}
		}
		i++;
	}


	return true;
}