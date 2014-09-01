#include "UICanvasCore.h"



bool UICanvasCore::drawSubCanvas(Canvas* sCanvas, pair<unsigned int, unsigned int>location, pair<unsigned int, unsigned int> size)
{
	unsigned int offsetSec = location.first + (location.second * this->canvas->getWidth());
	unsigned int offset = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int startCorner = location.first + (location.second * this->canvas->getWidth());
	for (unsigned int j = 0; j < (size.first * size.second); j++)
	{
		x++;
		if (j%sCanvas->getWidth() == 0)
		{
			y++;
			x = 0;
		}
		offset = x + y * this->canvas->getWidth();
		if ((offset + offsetSec) >= (this->canvas->page.size())) continue;
		
		if (sCanvas->page[j].a != 0)
		{
			this->canvas->page[offset + offsetSec].r = sCanvas->page[j].r;
			this->canvas->page[offset + offsetSec].g = sCanvas->page[j].g;
			this->canvas->page[offset + offsetSec].b = sCanvas->page[j].b;
			this->canvas->page[offset + offsetSec].a = sCanvas->page[j].a;
		}
		else
		{
			if (this->canvas->page[offset + offsetSec].a == 0) //if we want to do something to the empty areas..
			{
				//this->canvas->page[offset].r = 0;
				//this->canvas->page[offset].g = 50;
				//this->canvas->page[offset].b = 0;
				//this->canvas->page[offset].a = 255;
			}
			else //basic transparancy handling
			{
				this->canvas->page[offset + offsetSec] = blendPixel(sCanvas->page[j], this->canvas->page[offset + offsetSec]);
			}
		}
	}


	return true;
}