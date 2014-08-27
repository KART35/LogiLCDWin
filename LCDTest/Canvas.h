#pragma once
#include "LCD.h"
#include <stdint.h>
#include <utility>
#include <vector>

class Canvas 
{
	
	unsigned int 
		height, 
		width, 
		posX, 
		posY = 0;
	
public:
	struct pix
	{
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;
		uint8_t a = 0;
	};
	std::vector<pix> page;

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	Canvas( unsigned int height = 240, unsigned int width = 320, unsigned int posX = 0, unsigned int posY = 0) :
		page(height*width)
	{
		
		this->height = height;
		this->width = width;
		this->posX = posX;
		this->posY = posY;
	}
	
	std::pair<unsigned int, unsigned int> getLoc()
	{
		return std::make_pair(this->posX, this->posY);
	}

	std::pair<unsigned int, unsigned int> getSize()
	{
		return std::make_pair(this->height, this->width);
	}
	
	std::vector<pix> *getCanvas()
	{
		return &this->page;
	}

	
};


